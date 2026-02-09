#include <fmt/chrono.h>
#include <fmt/format.h>

#include "config.h"

void changeValueByParameter(int value)
{
    value = 99;
    fmt::print("Wert in changeValueByParameter: {}\n", value);
}

void changeValueByReference(int& ref)
{
    ref = 77;
    fmt::print("Wert in changeValueByReference: {}\n", ref);
}

auto main(int argc, char **argv) -> int
{

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", tfe24::PROJECT_NAME);

    // Teil 1: Grundlagen Referenzen
    fmt::print("\n--- Teil 1: Grundlagen Referenzen ---\n");
    
    int x = 10;
    int& r = x;
    
    fmt::print("Wert von x: {}\n", x);
    fmt::print("Wert von r: {}\n", r);
    
    r = 42;
    
    fmt::print("Nach Änderung über Referenz:\n");
    fmt::print("Wert von x: {}\n", x);
    fmt::print("Wert von r: {}\n", r);
    
    // Teil 2: Funktionen mit Referenzen
    fmt::print("\n--- Teil 2: Funktionen mit Referenzen ---\n");
    
    int y = 5;
    fmt::print("Ursprünglicher Wert von y: {}\n", y);
    
    changeValueByParameter(y);
    fmt::print("Nach changeValueByParameter - y: {}\n", y);
    
    changeValueByReference(y);
    fmt::print("Nach changeValueByReference - y: {}\n", y);

    return 0; /* exit gracefully*/
}
