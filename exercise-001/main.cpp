#include <fmt/chrono.h>
#include <fmt/format.h>

#include "config.h"

// --- Teil 2: Funktionen mit Referenzen ---

// Übergabe per Wert (Parameterübergabe)
void changeValueByParameter(int value) {
    fmt::print("   [changeValueByParameter] Wert innerhalb der Funktion (vor Änderung): {}\n", value);
    value = 99;
    fmt::print("   [changeValueByParameter] Wert innerhalb der Funktion (nach Änderung): {}\n", value);
}

// Übergabe per Referenz
void changeValueByReference(int& ref) {
    fmt::print("   [changeValueByReference] Wert innerhalb der Funktion (vor Änderung): {}\n", ref);
    ref = 77;
    fmt::print("   [changeValueByReference] Wert innerhalb der Funktion (nach Änderung): {}\n", ref);
}

auto main(int argc, char **argv) -> int
{

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", tfe24::PROJECT_NAME);

   // --- Teil 1: Grundlagen Referenzen ---
    int x = 10;
    int& r = x; // Referenz auf x

    fmt::print("--- Teil 1: Grundlagen Referenzen ---\n");
    fmt::print("x = {}, r = {}\n", x, r);

    r = 42; // Änderung über die Referenz
    fmt::print("Nach Änderung über r:\n");
    fmt::print("x = {}, r = {}\n\n", x, r);

    // --- Teil 3: Vergleich ---
    fmt::print("--- Teil 3: Vergleich ---\n");
    int y = 5;
    fmt::print("Vor changeValueByParameter: y = {}\n", y);
    changeValueByParameter(y);
    fmt::print("Nach changeValueByParameter: y = {}\n\n", y);

    fmt::print("Vor changeValueByReference: y = {}\n", y);
    changeValueByReference(y);
    fmt::print("Nach changeValueByReference: y = {}\n", y);

    return 0; /* exit gracefully +1*/
}
