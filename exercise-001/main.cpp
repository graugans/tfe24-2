#include <fmt/chrono.h>
#include <fmt/format.h>
#include "config.h"

// Teil 2: Funktionen mit Referenzen
void changeValueByParameter(int value)
{
    value = 1;
    fmt::print("Wert innerhalb Funktion (ByParameter): {}\n", value);
    return;
}
void changeValueByReference(int& ref)
{
    ref = 2;
    fmt::print("Wert innerhalb Funktion (ByReference): {}\n", ref);
    return;
}


int main()
{
// Teil 1: Grundlagen Referenzen
    int x = 10;
    int& r = x;
    fmt::print("Wert von x: {}\n", x);
    fmt::print("Wert von r: {}\n", r);
    r = 42;
    fmt::print("Wert von x: {}\n", x);
    fmt::print("Wert von r: {}\n\n", r);

// Teil 3: Vergleich
    int y = 5;
    changeValueByParameter(y);
    fmt::print("Wert von y: {}\n", y);
    changeValueByReference(y);
    fmt::print("Wert von y: {}\n\n", y);
    return 1;
}
