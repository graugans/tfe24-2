## Parameterraum / Teil 1
Da ich die Aufgabe nach dem vorgesehenen Abgabezeitraum bearbeite habe ich die "Vorlage" nicht angepasst, sondern "neu geschrieben". Das bedeutet in dem Fall, dass ich die Vorlage von https://github.com/CLIUtils/CLI11#usage kopiert und für meinen Fall angepasst habe. Die Änderungen sind nicht wirklich komplex, die Funktion der Variablen und Methoden geht aus dem Programmcode hervor.

## Den Zufall einordnen / Teil 2
Erstellen Sie einen ``std::vector`` mit der Größe von ``count`` und füllen diesen mit zufälligen Werten von 1-100.

Dafür wird als erstes der vector (``random_vec``) erstellt. Anschließend wird ein zufälliger Seed generiert. Dieser wird anschließend dem ``generator`` gefüttert. Die Codezeile ``std::uniform_int_distribution dis(1, 100);`` führt später dazu, dass die vom Generator zufällig generierten Bits am Ende gleich auf Zahlenwerte von 1 - 100 verteilt werden. Anders als in Python ist das hier also ein mehrstufiger Prozess. Um die richtige Anzahl von Werten anschließend in den Vektor zu "pushen" wird die anschließende for-Schleife benötigt.

## Zeig es mir Baby / Teil 3
Damit Sie den Zufall kennen, müssen Sie ihn ausgeben können. Verwenden Sie hierzu die ``{fmt}`` Bibliothek und erstellen Sie eine Funktion, um den Vektor auszugeben.

Die Funktion unter ``// Teil 3 der Aufgabe`` erfüllt den Zweck auf einfache Weise. Die Methode ``vector.size()`` macht es sehr einfach von Beginn, zum Ende des Vektors zu iterieren und dabei jeden Inhalt Auszugeben.

## Der Zufall in geordneten Bahnen / Teil 4

Sortieren Sie nun den Vector der Reihe nach. Das heißt die niedrigste Zahl zuerst. Das Ergebnis soll ebenfalls ausgegeben werden.

Die Funktion ``std::sort()`` sortiert den Vektor. Sofern man als Parameter ``VECTOR.begin(), VECTOR.end()`` eingibt, geschieht das in aufsteigender Reihenfolge, wie in mein Beispiel veranschaulicht.

## Strava für Vektoren / Teil 5

Damit Sie sich mit Ihren Kollegen messen können, interessiert Sie nur eine Sache. Geschwindigkeit. Wie schnell wurde der Vektor sortiert. Dazu nutzen Sie die Funktionen der Bibliothek ``std::chrono``

```cpp
auto start = std::chrono::system_clock::now();

/* do some work */

auto end = std::chrono::system_clock::now();
auto elapsed = end - start;
```

Vermutlich wird Ihr Rechner diese Aufgabe durchaus unter einer Sekunde lösen. Das heißt, Sie müssen ihn entweder mehr fordern oder eine andere Zeitbasis wählen.

```cpp
// this constructs a duration object using milliseconds
auto elapsed =
    std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
```

Sie haben es erfasst, die Ergebnisse sind wieder mit ``{fmt}`` auszugeben.

Die gegebenen Codeschnippsel wurden in den source-code integriert und funktionieren.

## Nach getaner Arbeit

Haben Sie alle Punkte erfolgreich abgearbeitet, erstellen Sie einen Merge-Request in Ihrem Fork und fügen mich ``graugans`` als Approval hinzu.

## Anmerkungen

- Verwenden Sie, falls möglich range based for loops siehe auch [es71](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#es71-prefer-a-range-for-statement-to-a-for-statement-when-there-is-a-choice) aus den Cpp Core Guidelines
- Achten Sie darauf, bei Parametern möglichst immer das Schlüsselwort ``const`` zu verwenden.

Diese Anmerkungen habe ich leider erst nach geschriebenem Code gesichtet, weswegen ich bestimmte Vorgaben möglicherweise nicht befolgt habe. 
