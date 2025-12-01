# Testat: MCP-Server in C++ mit Logging, Tankerkönig-API und Adressauflösung über Photon

## 1. Ziel des Testats

In diesem Testat implementieren Sie einen **MCP-Server (Model Context Protocol)** in **C++**, der

- über **stdin/stdout** per **JSON-RPC 2.0** mit einem MCP-Client kommuniziert,
- die **Tankerkoenig-API** nutzt, um reale Spritpreisdaten abzurufen,
- die **Photon-API** nutzt, um Adressen in Geokoordinaten umzuwandeln,
- ein **konfigurierbares Logging** besitzt (Konsole oder Datei),
- über **CLI11** konfiguriert wird,
- mit **nlohmann::json** JSON verarbeitet,
- und **Catch2**-basierte Unit-Tests enthält.

Nach Abschluss des Testats sollen Sie

- das **Model Context Protocol (MCP)** und die Rolle eines MCP-Servers verstehen,
- JSON-RPC in C++ verarbeiten und Tools bereitstellen,
- externe REST-APIs (Tankerkoenig & Photon) konsumieren,
- Logging sinnvoll strukturieren (Konsole/Datei, Log-Level),
- CLI11, nlohmann::json und Catch2 in einem integrierten Projekt einsetzen können.

---

## 2. Hintergrund

### 2.1 Model Context Protocol (MCP)

MCP ist ein offenes Protokoll, mit dem LLM-Clients (z. B. ChatGPT Desktop) externe Tools, Ressourcen und Prompts anbinden können. Ein MCP-Server

- läuft als separater Prozess,
- kommuniziert typischerweise über **stdin/stdout**,
- spricht **JSON-RPC 2.0**,
- stellt **Tools** bereit, die vom Client aufgerufen werden können.

Wichtige Methoden auf Serverseite:

- `server.initialize` – meldet Fähigkeiten des Servers,
- `tools.list` – liefert eine Liste verfügbarer Tools,
- `tools.call` – führt ein Tool mit Argumenten aus.

In diesem Testat fokussieren wir uns auf

- einen lokal laufenden Prozess, der über stdin/stdout angesprochen wird,
- die oben genannten Kernmethoden.

### 2.2 JSON-RPC 2.0 – Das Kommunikationsprotokoll

**JSON-RPC 2.0** ist ein zustandsloses, leichtgewichtiges Remote Procedure Call (RPC) Protokoll. Es definiert, wie Client und Server strukturiert miteinander kommunizieren.

#### 2.2.1 Grundprinzipien

- **Transport-agnostisch:** Funktioniert über HTTP, WebSockets, stdin/stdout, etc.
- **JSON-basiert:** Alle Nachrichten sind gültige JSON-Objekte
- **Zustandslos:** Jede Anfrage ist unabhängig
- **Bidirektional:** Sowohl Client als auch Server können Requests senden

#### 2.2.2 Nachrichtentypen

**Request (Anfrage):**

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "tools.list",
  "params": {}
}
```

- `jsonrpc` – **Pflicht**, immer `"2.0"`
- `id` – **Pflicht** für Requests, die eine Antwort erwarten (String oder Number)
- `method` – **Pflicht**, Name der aufzurufenden Methode (String)
- `params` – **Optional**, Parameter als Object oder Array

**Notification (Request ohne Antwort):**

Eine Notification ist ein Request **ohne** `id`-Feld. Der Server sendet keine Response.

**Success Response (Erfolgreiche Antwort):**

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "tools": [
      {
        "name": "listStations",
        "description": "Tankstellen im Umkreis finden"
      }
    ]
  }
}
```

- `jsonrpc` – **Pflicht**, immer `"2.0"`
- `id` – **Pflicht**, muss mit Request-ID übereinstimmen
- `result` – **Pflicht**, Ergebnis der Methode (beliebiger JSON-Typ)

**Error Response (Fehlerantwort):**

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "error": {
    "code": -32601,
    "message": "Method not found",
    "data": "Unknown method: tools.foo"
  }
}
```

- `jsonrpc` – **Pflicht**, immer `"2.0"`
- `id` – **Pflicht**, ID des fehlgeschlagenen Requests (oder `null` bei Parse-Fehlern)
- `error` – **Pflicht**, Error-Object mit:
  - `code` – Integer, vordefinierte Error-Codes
  - `message` – String, kurze Fehlerbeschreibung
  - `data` – **Optional**, zusätzliche Fehlerinformationen

#### 2.2.3 Standard Error-Codes

| Code | Message | Bedeutung |
|------|---------|-----------|
| -32700 | Parse error | Ungültiges JSON |
| -32600 | Invalid Request | JSON ist kein gültiger Request |
| -32601 | Method not found | Methode existiert nicht |
| -32602 | Invalid params | Ungültige Parameter |
| -32603 | Internal error | Interner Server-Fehler |

Custom Error-Codes sollten außerhalb des Bereichs -32768 bis -32000 liegen.

#### 2.2.4 Batch-Requests (Optional)

JSON-RPC 2.0 unterstützt das Senden mehrerer Requests in einem Array:

```json
[
  {"jsonrpc": "2.0", "id": 1, "method": "tools.list"},
  {"jsonrpc": "2.0", "id": 2, "method": "tools.call", "params": {"name": "listStations"}}
]
```

**Hinweis:** Batch-Requests sind **optional** für dieses Testat.

#### 2.2.5 Wichtig für Ihre Implementierung

- **Immer validieren:** Prüfen Sie, ob `jsonrpc: "2.0"` vorhanden ist
- **Error-Handling:** Ungültiges JSON → Error -32700, unbekannte Methode → Error -32601
- **ID-Matching:** Response-ID muss immer mit Request-ID übereinstimmen
- **Null-ID:** Bei Parse-Fehlern (bevor ID gelesen werden kann) ist `"id": null` zulässig

**Referenz:** [JSON-RPC 2.0 Specification](https://www.jsonrpc.org/specification)

---

### 2.3 Tankerkönig-API (Spritpreise)

Die Tankerkönig-API stellt aktuelle Spritpreise und Tankstelleninformationen zur Verfügung:

- **Umkreissuche** – `list.php`
- **Preisabfrage** – `prices.php`
- **Details** – `detail.php`

Typische Parameter für `list.php`:

- `lat` – Breitengrad,
- `lng` – Längengrad,
- `rad` – Radius in Kilometern (bis 25),
- `type` – Spritsorte (`e5`, `e10`, `diesel`, `all`),
- `sort` – Sortierung (`price` oder `dist`),
- `apikey` – persönlicher API-Key.

**Wichtige Hinweise:**

- Für die Nutzung ist ein **persönlicher API-Key** erforderlich.
- API-Keys dürfen **nicht** in öffentliche Repositories (z. B. GitHub) eingecheckt werden.
- Sie sollen Anfragen in vernünftigen Intervallen durchführen (kein Spamming).

### 2.4 Photon-API (Geocoding)

Photon (photon.komoot.io) ist eine Geocoding-API, die aus einer Adresse Koordinaten (Longitude/Latitude) erzeugt. Ein typischer Request:

```text
https://photon.komoot.io/api/?q=<adresse>&limit=1
```

Die Antwort ist GeoJSON. Interessant ist insbesondere:

```json
"geometry": {
  "type": "Point",
  "coordinates": [ <lon>, <lat> ]
}
```

**Wichtig:** GeoJSON nutzt immer die Reihenfolge `[longitude, latitude]`. Tankerkönig erwartet dagegen `lat=<latitude>&lng=<longitude>`.

---

## 3. Sicherer Umgang mit API-Keys (Security Best Practices)

### 3.1 Warum ist das wichtig?

API-Keys sind **Zugangsdaten** zu externen Diensten. Wenn sie in falsche Hände geraten, können Dritte:

- Ihre Kontingente aufbrauchen,
- Kosten verursachen (bei kostenpflichtigen APIs),
- im schlimmsten Fall Zugriff auf sensible Daten erhalten.

**Grundregel:** API-Keys dürfen **niemals** in öffentlichen Repositories (GitHub, GitLab etc.) landen.

### 3.2 Optionen für die sichere Speicherung

Im Folgenden werden verschiedene Ansätze mit ihren Vor- und Nachteilen vorgestellt.

#### Option 1: Umgebungsvariablen (empfohlen für Entwicklung)

**Beschreibung:**
Der API-Key wird als Umgebungsvariable gesetzt und vom Programm zur Laufzeit ausgelesen.

**Vorteile:**

- ✅ Einfach zu verwenden
- ✅ Key bleibt außerhalb des Quellcodes
- ✅ Gut für lokale Entwicklung und CI/CD-Pipelines
- ✅ Funktioniert plattformübergreifend

**Nachteile:**

- ⚠️ Auf gemeinsam genutzten Systemen können andere Benutzer mit ausreichenden Rechten die Variablen einsehen
- ⚠️ Keine automatische Verschlüsselung
- ⚠️ Bei vielen Keys/Projekten wird die Verwaltung unübersichtlich

**Beispiele:**

```bash
# Setzen (temporär für die aktuelle Shell-Session)
export TANKERKOENIG_API_KEY="ihr_geheimer_key"

# Programm starten
./mcp-tanker --apikey=$TANKERKOENIG_API_KEY

# Oder: Programm liest automatisch aus der Umgebungsvariable
./mcp-tanker
```

In C++:

```cpp
#include <cstdlib>
#include <string>

std::string apikey = std::getenv("TANKERKOENIG_API_KEY")
                     ? std::getenv("TANKERKOENIG_API_KEY")
                     : "";
if (apikey.empty()) {
    std::cerr << "Error: TANKERKOENIG_API_KEY not set\n";
    return 1;
}
```

**Empfehlung für dieses Testat:**
Lesen Sie den API-Key aus der Umgebungsvariable `TANKERKOENIG_API_KEY`, falls `--apikey` nicht übergeben wurde.

---

#### Option 2: `.env`-Datei + `.gitignore` (sehr beliebt für Entwicklung)

**Beschreibung:**
Eine lokale Datei (z. B. `.env`) enthält Key-Value-Paare. Diese Datei wird **nicht** ins Repository eingecheckt.

**Vorteile:**

- ✅ Sehr einfach zu handhaben
- ✅ Klarer Workflow: `.env` lokal, `.env.example` (ohne echte Keys) im Repo
- ✅ Viele Frameworks und Tools unterstützen `.env` nativ

**Nachteile:**

- ⚠️ Wenn `.env` versehentlich committed wird, sind Keys kompromittiert
- ⚠️ Datei liegt unverschlüsselt auf der Festplatte
- ⚠️ Kein Schutz vor lokalem Zugriff durch andere Prozesse/Benutzer

**Beispiel:**

`.env` (lokal, **nicht** ins Repo):

```bash
TANKERKOENIG_API_KEY=ihr_geheimer_key
```

`.env.example` (committet ins Repo, **ohne** echte Keys):

```bash
TANKERKOENIG_API_KEY=
```

`.gitignore`:

```gitignore
.env
```

**In C++ nutzen:**
Sie können eine kleine Hilfsfunktion schreiben, die `.env` parst, oder C++-Libraries wie [cpp-dotenv](https://github.com/laserpants/cpp-dotenv) verwenden.

**Wichtig:**
Prüfen Sie **vor jedem Commit** mit `git status`, dass `.env` nicht versehentlich eingecheckt wird!

---

### 3.3 Weitere Sicherheitsmaßnahmen

- **`.gitignore` konsequent nutzen:**
  Tragen Sie Dateien wie `.env`, `config.local.json` etc. ein, **bevor** Sie sie erstellen.

- **Pre-Commit Hooks:**
  Tools wie [`detect-secrets`](https://github.com/Yelp/detect-secrets), [`git-secrets`](https://github.com/awslabs/git-secrets) oder [`truffleHog`](https://github.com/trufflesecurity/truffleHog) scannen Commits auf versehentlich eingecheckte Secrets.

  Beispiel (git-secrets):

  ```bash
  git secrets --install
  git secrets --register-aws
  ```

- **Repository scannen:**
  Nutzen Sie Tools wie `gitleaks` oder `truffleHog`, um das gesamte Repo (inkl. Historie) nach Secrets zu durchsuchen.

- **Bei Leaks sofort handeln:**
  1. Key **sofort** revoken/rotieren (neuen Key generieren, alten deaktivieren).
  2. Prüfen, ob der Key missbraucht wurde (Logs, Abrechnungen).
  3. Ggf. aus der Git-Historie entfernen (z. B. mit `git filter-repo` oder BFG Repo-Cleaner) – **Vorsicht:** ändert die Historie!

- **Prinzip der geringsten Rechte (Least Privilege):**
  Geben Sie API-Keys nur die minimal nötigen Berechtigungen. Tankerkönig erlaubt z. B. nur Lesezugriff – das ist optimal.

- **Logging & Monitoring:**
  Loggen Sie **niemals** API-Keys. Überwachen Sie ungewöhnliche Nutzungsmuster (z. B. unerwartete Zugriffe).

---

### 3.4 Nützliche Tools & Links

**Scanning-Tools:**

- [git-secrets](https://github.com/awslabs/git-secrets) – AWS-fokussiert, aber erweiterbar
- [truffleHog](https://github.com/trufflesecurity/truffleHog) – durchsucht Git-Historie nach Secrets
- [gitleaks](https://github.com/gitleaks/gitleaks) – schneller Secret-Scanner
- [detect-secrets](https://github.com/Yelp/detect-secrets) – Pre-Commit-Hook von Yelp

**Environment Management für C++:**

- [cpp-dotenv](https://github.com/laserpants/cpp-dotenv) – `.env`-Datei Parser für C++
- Eigene einfache Implementierung zum Parsen von `.env`-Dateien

---

### 3.5 Empfehlung für dieses Testat

**Für lokale Entwicklung:**

1. **Umgebungsvariable** oder **`.env`-Datei** nutzen.
2. `.env` in `.gitignore` eintragen.
3. `.env.example` (nur mit Variablennamen, ohne Werte) ins Repo committen.
4. In der README dokumentieren, wie Studierende ihren eigenen API-Key setzen.

**Beispiel `.env.example`:**

```bash
# Tankerkoenig API Key
# Registrierung: https://creativecommons.tankerkoenig.de/
TANKERKOENIG_API_KEY=
```

**Beispiel-Dokumentation in der README:**

```text
## API-Key einrichten

1. Registrieren Sie sich bei [Tankerkoenig](https://creativecommons.tankerkoenig.de/)
   und erhalten Sie einen API-Key.

2. Setzen Sie den Key als Umgebungsvariable:

   export TANKERKOENIG_API_KEY="ihr_key_hier"

   Alternativ: Erstellen Sie eine `.env`-Datei im Projekt-Root:

   TANKERKOENIG_API_KEY=ihr_key_hier


3. Starten Sie den Server:

   ./mcp-tanker
```

**Für Teamarbeit / Abgabe:**

- Teilen Sie **niemals** Ihren echten Key in Abgaben oder öffentlichen Foren.
- Nutzen Sie Test-Keys mit minimalen Rechten oder bitten Sie Reviewer, ihren eigenen Key zu verwenden.
- Dokumentieren Sie klar, wie der Key zu setzen ist.

**Hinweis für fortgeschrittene Szenarien:**

Falls Sie später in Produktivumgebungen arbeiten, sollten Sie sich mit **Cloud Secret Managern** (AWS Secrets Manager, Google Cloud Secret Manager, Azure Key Vault, HashiCorp Vault) vertraut machen. Diese bieten zusätzliche Features wie Zugriffskontrolle, Audit-Logs und automatische Key-Rotation. Für dieses Testat sind sie jedoch nicht erforderlich.

---

### 3.6 Checkliste: Sichere API-Key-Verwaltung

- [ ] ✅ API-Keys niemals direkt im Quellcode speichern
- [ ] ✅ `.env` in `.gitignore` aufnehmen
- [ ] ✅ `.env.example` (ohne echte Keys) ins Repo committen
- [ ] ✅ Umgebungsvariablen im Code verwenden (`std::getenv`)
- [ ] ✅ Pre-Commit Hooks einrichten (`detect-secrets`, `git-secrets`)
- [ ] ✅ Repository vor Abgabe scannen (`gitleaks`, `truffleHog`)
- [ ] ✅ Bei Leaks: Key sofort rotieren/revoken
- [ ] ✅ Prinzip der geringsten Rechte: Keys nur minimal nötige Berechtigungen geben
- [ ] ✅ Logging: Niemals API-Keys in Logs ausgeben
- [ ] ✅ Dokumentation: Klare Anweisungen für Teammitglieder/Reviewer

---

### 3.7 Zusammenfassung

Für dieses Testat reicht die Verwendung von **Umgebungsvariablen** oder einer **`.env`-Datei** (mit `.gitignore`) vollkommen aus. Achten Sie darauf, dass Ihr API-Key niemals ins Repository gelangt, und dokumentieren Sie klar, wie Reviewer/Dozenten ihren eigenen Key setzen können.---

## 4. Aufgabenübersicht

Das Testat umfasst folgende Teile:

1. **A – MCP-Server-Grundgerüst in C++**
2. **B – Tankerkönig-Tools als MCP-Tools**
3. **C – Logging (Konsole/Datei)**
4. **D – CLI-Konfiguration mit CLI11**
5. **E – Unit-Tests mit Catch2**
6. **F – Adressauflösung über Photon (Addendum)**
7. **G – Bonusaufgaben (optional)**

---

## 5. Teil A – Minimaler MCP-Server in C++

Implementieren Sie einen MCP-Server in C++, der

- über **stdin/stdout** JSON-RPC-Requests verarbeitet,
- mindestens die Methoden
  - `server.initialize`,
  - `tools.list`,
  - `tools.call`
  unterstützt,
- mit **nlohmann::json** arbeitet.

### 5.1 Anforderungen

- **Sprache:** C++17 oder neuer
- **Build-System:** CMake
- **JSON-Library:** nlohmann::json
- **Fehlerbehandlung (JSON-RPC):**
  - Ungültiges JSON ⇒ Error-Code `-32700` („Parse error“)
  - Unbekannte Methode ⇒ Error-Code `-32601` („Method not found“)
- Nachrichtenformat gemäß JSON-RPC 2.0, z. B.:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "server.initialize",
  "params": { }
}
```

**Vereinfachung (Pflicht):**
Zunächst ist es ausreichend, wenn Sie annehmen, dass **pro Zeile** genau eine vollständige JSON-RPC-Nachricht übertragen wird (Zeilenbasiertes Framing).

> Hinweis: In den Bonusaufgaben wird optional „echtes" `Content-Length`-Framing gefordert.

---

## 6. Teil B – Tankerkönig-Tools

Ihr MCP-Server soll mindestens **zwei Tools** bereitstellen, die die Tankerkönig-API verwenden.

### 6.1 Tool 1: `listStations`

**Zweck:** Tankstellen im Umkreis einer Position abfragen (`list.php`).

**Input (Tool-Argumente):**

- `lat: double` – Breitengrad
- `lng: double` – Längengrad
- `rad: double` – Radius in km (1–25)
- `type: string` – `"e5"`, `"e10"`, `"diesel"` oder `"all"`
- optional: `sort: string` – `"price"` oder `"dist"` (Standard: `"price"`)

**Verhalten:**

1. HTTP-GET-Request an `.../json/list.php` mit den oben genannten Parametern.
2. JSON-Antwort parsen (nlohmann::json).
3. Das Feld `ok` prüfen:
   - Falls `ok == false`: MCP-Fehlerantwort mit Fehlertext zurückgeben.
4. Eine sinnvolle, reduzierte Datenstruktur zurückgeben, z. B. Liste von Objekten mit:
   - `id`, `name`, `brand`, `place`, `lat`, `lng`, `dist`, `e5`, `e10`, `diesel`, `isOpen`.

### 6.2 Tool 2: `getPrices`

**Zweck:** Preise für eine Menge bekannter Tankstellen abfragen (`prices.php`).

**Input:**

- `ids: array<string>` – Liste von Tankstellen-IDs (max. 10 IDs)

**Verhalten:**

1. HTTP-GET-Request an `.../json/prices.php` mit `ids=...`.
2. `ok`-Flag prüfen.
3. Das Ergebnis in ein MCP-kompatibles Format überführen, z. B. eine Map von ID → Preisinfo.

### 6.3 Implementierungshinweise

- Kapseln Sie die HTTP-Logik in eine Klasse, z. B. `TankerkoenigClient`.
- Verwenden Sie eine geeignete HTTP-Library (z. B. libcurl, cpr, Boost.Beast) und dokumentieren Sie Ihre Wahl in der README.
- Achten Sie auf Zeitouts und einfache Fehlerbehandlung (HTTP-Status, Netzwerkfehler).

---

## 7. Teil C – Logging (Konsole/Datei)

In Anlehnung an frühere Übungen (z. B. exercise-030) soll Ihr MCP-Server ein konfigurierbares Logging besitzen.

### 7.1 Anforderungen an das Logging

Implementieren Sie eine Logger-Komponente, die:

- mindestens die Log-Level `ERROR`, `WARN`, `INFO`, `DEBUG` unterstützt,
- wahlweise in
  - die **Konsole** (stdout oder stderr) oder
  - eine **Datei**
  schreibt.

**Log-Nachrichten sollten enthalten:**

- Timestamp,
- Log-Level,
- Nachrichtentext,
- optional: Kontext (z. B. Request-ID, Tool-Name).

### 7.2 Pflicht-Logpunkte

Es sollen mindestens folgende Ereignisse geloggt werden:

- Start des Servers (inkl. Konfiguration: Log-Level, Log-Ziel, ggf. Pfad zur Log-Datei).
- Jeder eingehende JSON-RPC-Request (ggf. gekürzt, ohne sensible Inhalte).
- Jeder ausgehende JSON-RPC-Response (optional gekürzt).
- Jeder HTTP-Request an Tankerkönig (z. B. URL ohne API-Key, Ergebnis `ok`/`!ok`).

---

## 8. Teil D – CLI-Konfiguration mit CLI11

Nutzen Sie **CLI11**, um Ihren Server per Kommandozeile zu konfigurieren.

### 8.1 Pflichtoptionen

Ihr Server-Binary soll mindestens folgende Optionen unterstützen:

- `--log-level`, `-l`
  - Werte: `error`, `warn`, `info`, `debug`
  - Standardwert: `info`
- `--log-target`
  - Werte: `console`, `file`
  - Standardwert: `console`
- `--log-file`
  - Pfad zur Log-Datei (nur relevant, wenn `--log-target=file`)
- `--apikey`
  - API-Key für Tankerkönig
  - Empfehlung: Wenn nicht gesetzt, Key aus einer Umgebungsvariablen lesen (z. B. `TANKERKOENIG_API_KEY`).

Optionale zusätzliche Parameter (nicht Pflicht, aber sinnvoll):

- Standardradius (`--default-radius`),
- Standard-Spritsorte (`--default-type`),
- HTTP-Timeouts.

### 8.2 Beispielaufrufe

Beispiele, die in der README dokumentiert werden sollen:

```bash
./mcp-tanker --log-level=debug --log-target=console

./mcp-tanker --log-level=info --log-target=file --log-file=server.log \
             --apikey=$TANKERKOENIG_API_KEY
```

---

## 9. Teil E – Unit-Tests mit Catch2

Schreiben Sie Unit-Tests mit **Catch2** für zentrale Teile Ihres Systems.

### 9.1 Pflicht-Tests

- **Logger-Logik**
  - Testen Sie die Log-Level-Filterung (z. B. bei `INFO` werden `DEBUG`-Nachrichten unterdrückt).
  - Testen Sie die Formatierung der Nachrichten (mindestens: Level + Text).
  - Um Dateizugriffe zu vermeiden, können Sie über einen String-Stream testen.

- **Tankerkoenig-Client-Logik (Parsing)**
  - Funktion(en) zur Verarbeitung der JSON-Antworten:
    - korrektes Auswerten des `ok`-Flags,
    - korrekte Extraktion relevanter Felder,
    - sinnvolle Fehlerbehandlung (z. B. fehlende Felder).

### 9.2 Struktur

Legen Sie z. B. einen Ordner `tests/` an mit Dateien wie:

- `logger_tests.cpp`
- `tankerkoenig_tests.cpp`

Bauen Sie die Tests über eine separate CMake-Target-Konfiguration (z. B. `add_executable(tests ...)` + `add_test(...)`).

---

## 10. Teil F – Adressauflösung über Photon (Addendum)

### 10.1 Motivation

Bisher müssen für `listStations` Koordinaten (lat/lng) direkt übergeben werden. Für eine komfortablere Nutzung soll der Server zusätzlich **Adressen in Koordinaten umwandeln** und daraus automatisch Tankerkönig-Umkreissuchen bauen können.

Hierzu wird die **Photon-API** genutzt.

### 10.2 Photon-Request und relevante Felder

Ein einfacher Photon-Request sieht so aus:

```text
https://photon.komoot.io/api/?q=<adresse>&limit=1
```

Beispiel (Adresse URL-codiert):

```bash
curl "https://photon.komoot.io/api/?q=Unter%20den%20Linden%201%20Berlin&limit=1"
```

In der JSON-Antwort findet sich ein Eintrag im `features`-Array, z. B.:

```json
{
  "type": "Feature",
  "geometry": {
    "type": "Point",
    "coordinates": [
      13.380294034887884,
      52.51631251016608
    ]
  },
  "properties": {
    "name": "Unter den Linden 1",
    "city": "Berlin",
    "...": "..."
  }
}
```

Wichtig ist das Feld:

```json
"coordinates": [ <lon>, <lat> ]
```

### 10.3 Koordinatenreihenfolge anpassen

Photon nutzt GeoJSON-Konvention:

- `coordinates[0]` = Longitude (**lon**),
- `coordinates[1]` = Latitude (**lat**).

Tankerkoenig erwartet jedoch Parameter in der Form:

```text
lat=<lat>&lng=<lon>
```

Sie müssen also **die Reihenfolge explizit umdrehen**, bevor Sie den Tankerkönig-Request aufbauen.

### 10.4 Neues MCP-Tool: `findByAddress`

Erweitern Sie Ihren MCP-Server um ein weiteres Tool:

#### Tool: `findByAddress`

**Eingabeparameter:**

- `address: string` (Pflicht)
- optional:
  - `rad: double` – Radius in km (Standard: 5)
  - `type: string` – Spritsorte; Werte: `e5`, `e10`, `diesel`, `all` (Standard: `e5`)
  - `sort: string` – `"price"` oder `"dist"` (Standard: `"price"`)

**Ablauf:**

1. Photon-API aufrufen:
   - Adresse an Photon senden,
   - Antwort parsen,
   - ersten Treffer aus `features[0]` auswählen.
2. Longitude/Latitude extrahieren:
   - `lon = coordinates[0]`,
   - `lat = coordinates[1]`.
3. Tankerkönig-Request für `list.php` konstruieren:
   - `lat=<lat>`,
   - `lng=<lon>`,
   - `rad`, `type`, `sort`, `apikey` wie gewohnt.
4. Ergebnis aufbereiten:
   - analog zu `listStations` (Liste von Tankstellen mit Preisen etc.).
5. Ergebnis als MCP-Tool-Response zurückgeben.

#### Fehlerbehandlung

- **Keine Treffer in Photon** (leeres `features`-Array):
  - MCP-Fehler zurückgeben (z. B. „Adresse nicht gefunden“).
- **Photon nicht erreichbar / HTTP-Fehler**:
  - MCP-Fehler mit geeigneter Fehlermeldung (z. B. „Geocoding-Service nicht erreichbar“).
- **Ungültige oder unvollständige Antwort**:
  - Ebenfalls MCP-Fehler mit Erklärung.
- **Tankerkoenig `ok == false`**:
  - MCP-Fehler mit dem von Tankerkönig gelieferten Fehlertext.

### 10.5 Dokumentationserweiterung

Erweitern Sie Ihre Projekt-README um einen Abschnitt zur Adressauflösung:

- kurze Erklärung von Photon,
- Beschreibung der Koordinatenreihenfolge `[lon, lat]` und der Umkehrung für Tankerkönig,
- mindestens ein vollständiges Beispiel:

  1. Adresse (z. B. „Unter den Linden 1, Berlin“)
  2. Photon-Antwort (gekürzt, relevanter Ausschnitt)
  3. abgeleitete `lat`/`lng`-Werte
  4. finaler Tankerkönig-Request
  5. Beispiel-Request/-Response des MCP-Tools `findByAddress` über den MCP-Client

---

## 11. Teil G – Bonusaufgaben (optional)

Für zusätzliche Punkte können Sie eine oder mehrere der folgenden Erweiterungen implementieren:

1. **Content-Length-Framing**
   - Implementieren Sie ein Protokoll, das Header der Form

     ```text
     Content-Length: 123

     { "jsonrpc": "2.0", ... }
     ```

     liest, die Länge parst und exakt diese Anzahl an Bytes als JSON-RPC-Nachricht verarbeitet.

2. **Separates MCP-Tool `geocodeAddress`**
   - Tool, das nur die Photon-Geocodierung kapselt und eine Liste von möglichen Treffern zurückgibt (mit Name, Stadt, Koordinaten).
   - `findByAddress` könnte dieses Tool intern nutzen.

3. **Mehrere Photon-Treffer berücksichtigen**
   - Statt automatisch `features[0]` zu verwenden, ermöglichen Sie:
     - die Auswahl des n-ten Treffers (z. B. via Parameter `index`), oder
     - eine filterbasierte Auswahl.

4. **Address-Cache**
   - Implementieren Sie einen einfachen Cache (z. B. `std::unordered_map<std::string, Koordinaten>`), um häufig genutzte Adressen nicht jedes Mal neu bei Photon abzufragen.

5. **Erweitertes Logging**
   - z. B. rotierende Logfiles, JSON-basiertes Logging, zusätzliche Kontextinformationen (Request-ID, Dauer von HTTP-Requests).

---

## 12. Testen mit MCP-Clients

Sie müssen Ihren MCP-Server mit mindestens einem MCP-fähigen Client testen.

### 12.1 Variante A – `mcp-cli` (empfohlen)

1. Installation (Node.js erforderlich):

   ```bash
   npm install -g @modelcontextprotocol/cli
   ```

2. Server starten, z. B.:

   ```bash
   ./mcp-tanker --log-level=debug --log-target=console --apikey=$TANKERKOENIG_API_KEY
   ```

3. Verbindung mit `mcp-cli` herstellen:

   ```bash
   mcp connect ./mcp-tanker
   ```

4. Tools anzeigen:

   ```bash
   mcp list-tools
   ```

5. Beispielaufrufe (die Sie in der README dokumentieren):

   - `listStations` mit Koordinaten
   - `getPrices` mit Tankstellen-IDs
   - `findByAddress` mit einer Adresse

   Beispiel:

   ```bash
   mcp call findByAddress '{"address":"Unter den Linden 1, Berlin","rad":5,"type":"e5","sort":"price"}'
   ```

   Notieren Sie dazu passende Ausschnitte aus dem Log.

### 12.2 Variante B – ChatGPT Desktop / anderer MCP-Client

Falls Sie einen grafischen MCP-Client (z. B. ChatGPT Desktop oder VS Code mit MCP-Unterstützung) verwenden:

- Dokumentieren Sie die verwendete Konfiguration (z. B. `servers.json`),
- Fügen Sie Screenshots bei, die zeigen,
  - dass Ihr Server erkannt wurde,
  - dass Ihre Tools (`listStations`, `getPrices`, `findByAddress`) sichtbar sind,
  - und dass ein Beispielaufruf erfolgreich durchgeführt wurde.

---

## 13. Projektstruktur & Abgabe

Vorgeschlagene Projektstruktur:

```text
mcp-tankerkoenig-testat/
├─ CMakeLists.txt
├─ src/
│  ├─ main.cpp
│  ├─ mcp_server.hpp / .cpp
│  ├─ logger.hpp / .cpp
│  ├─ tankerkoenig_client.hpp / .cpp
│  ├─ photon_client.hpp / .cpp
│  ├─ tools.hpp / .cpp
├─ include/           (optional)
├─ tests/
│  ├─ logger_tests.cpp
│  ├─ tankerkoenig_tests.cpp
│  ├─ photon_tests.cpp (optional)
├─ third_party/       (CLI11, Catch2, nlohmann, ggf. HTTP-Lib)
└─ README.md
```

Ihre `README.md` soll mindestens enthalten:

1. Kurzbeschreibung des Projekts und der Lernziele,
2. Build-Anleitung (Abhängigkeiten, CMake-Befehle, Besonderheiten für HTTP-Library),
3. Beschreibung der CLI-Optionen (CLI11) mit Beispielaufrufen,
4. Beschreibung der MCP-Tools (`listStations`, `getPrices`, `findByAddress`, ggf. weitere),
5. Hinweise zur Verwendung des Tankerkönig-API-Keys (z. B. über Umgebungsvariable, nicht ins Repo einchecken),
6. Beispiel-JSONs für Requests und Responses,
7. kurze Beschreibung der Unit-Tests (Catch2),
8. kurze Erklärung der Photon-Integration inkl. Beispiel.

---

## 14. Bewertungskriterien

Die Bewertung erfolgt nach folgenden Kriterien:

1. **Funktionalität (40 %)**
   - MCP-Basisfunktionen (`server.initialize`, `tools.list`, `tools.call`) funktionieren.
   - Tools `listStations`, `getPrices` und `findByAddress` verhalten sich wie beschrieben.
   - Sinnvolle Fehlerbehandlung bei ungültigem Input und API-Fehlern.

2. **Codequalität & Struktur (10 %)**
   - Klare Strukturierung (Server, Logger, Clients für Tankerkönig/Photon, Tools).
   - Lesbarer, wartbarer Code (Namen, Kommentare, Modularität).
   - Vermeidung unnötiger globaler Zustände.

3. **Protokolltreue & Robustheit (15 %)**
   - korrekte JSON-RPC-Struktur,
   - hilfreiche Fehlermeldungen bei Protokollfehlern,
   - robuste Behandlung von Netzwerkfehlern.

4. **Logging & CLI (10 %)**
   - Logging wie gefordert implementiert (Level, Ziel, Pflicht-Logpunkte),
   - sinnvolle CLI11-Konfiguration, verständliche Hilfe/Usage.

5. **Tests & Dokumentation (25 %)**
   - Catch2-Tests für zentrale Komponenten,
   - aussagekräftige README mit Beispielen und Screenshots/Logauszügen.

**Bonuspunkte** können Sie durch gelöste Bonusaufgaben (Content-Length-Framing, zusätzliche Tools, Caching, erweitertes Logging etc.) erreichen.

---

Viel Erfolg – und denken Sie daran:

- API-Keys niemals ins Repository einchecken,
- sensible Daten nicht loggen,
- und bei HTTP-APIs immer mit geeigneter Fehlerbehandlung zu arbeiten.

## Abgabe

Die Abgabe erfolgt bis spätestens 01.03.2025 um 23:59 Uhr. Über einen Pull-Request im spezifische Team Repository. Erstellen Sie hierzu einen Branch `testat-001` analog zu folgender Graphik:

![Git Branching Strategie - Testat Workflow](https://mermaid.ink/img/pako:eNqdkMEKwjAMhl-l5DxhXnsWNmEn9dhL7LJ1uLajSw9j7N2tiAgyRRYI5CfJ94fMoH1NIEG0HRcBByOqk1ROPEN7azv-Jq8BnTaCaWTkXZ7v_9xbxzSEHANt52hD-uYjrx1kKbS0xeLFtNi5D9rbRvA0kBTlsSirlJffcMggARKwTn-fH00FbMiSApnKmhqMPStQbkmjGNmfJ6dBcoiUQRxqZDp02Aa0IBvsR1ruc2aHwg?type=png)

Sie entwickeln Ihre Features in separaten Branches welche Sie jeweils mittels Pull-Request in Ihren Branch `testat-001` mergen.

**Wichtig:** Sie dürfen Ihren Branch `testat-001` auf keinen Fall in main mergen.

### Disqualifikation

Sollte eine oder mehrere Gruppen voneinander abschreiben, oder identischen Quellcode abliefern werden beide Gruppen disqualifiziert und das Testat gilt als nicht bestanden.
