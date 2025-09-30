#include <fmt/core.h>
// Funktion: Übergabe per Wert
void changeValueByParameter(int value) {
    value = 99;
    fmt::print("[changeValueByParameter] Wert in Funktion: {}\n", value);
}

// Funktion: Übergabe per Zeiger
void changeValueByPointer(int* ptr) {
    *ptr = 77;
    fmt::print("[changeValueByPointer] Wert in Funktion: {}\n", *ptr);
}
#include <fmt/chrono.h>
#include <fmt/format.h>

#include "config.h"

auto main(int argc, char **argv) -> int
{


    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", tfe24::PROJECT_NAME);
    // 1. Legen Sie eine int-Variable x mit dem Wert 10 an.
    int x = 10;
    // 2. Deklarieren Sie einen Zeiger p, der auf x zeigt.
    int* p = &x;

    // 3. Geben Sie mit fmt::print den Wert von x und die Adresse von x aus.
    fmt::print("Wert von x: {}\n", x);
    fmt::print("Adresse von x: {}\n", fmt::ptr(&x));

    // 4. Geben Sie den Wert aus, auf den der Zeiger p zeigt, sowie die Adresse, die in p gespeichert ist.
    fmt::print("Wert auf den p zeigt: {}\n", *p);
    fmt::print("Adresse in p: {}\n", fmt::ptr(p));

    // 5. Ändern Sie den Wert von x über den Zeiger p auf 42.
    *p = 42;

    // 6. Geben Sie erneut den Wert von x und den Wert aus, auf den p zeigt.
    fmt::print("Neuer Wert von x: {}\n", x);
    fmt::print("Neuer Wert auf den p zeigt: {}\n", *p);

        // Teil 2: Dynamische Speicherverwaltung
    double* d = new double(3.1415);   // Speicher im Heap reservieren
    fmt::print("Wert von d: {}\n", *d);     // Zugriff über Dereferenzierung
    fmt::print("Adresse von d: {}\n", fmt::ptr(d));
    delete d;                         // Speicher wieder freigeben

    // Teil 3: Funktionen mit Zeigern
    int y = 5;
    fmt::print("Vor changeValueByParameter: y = {}\n", y);
    changeValueByParameter(y);
    fmt::print("Nach changeValueByParameter: y = {}\n", y);

    fmt::print("Vor changeValueByPointer: y = {}\n", y);
    changeValueByPointer(&y);
    fmt::print("Nach changeValueByPointer: y = {}\n", y);

    return 0; /* exit gracefully*/
}
