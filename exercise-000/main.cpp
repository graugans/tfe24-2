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


    // --- Teil 1: Zeiger-Grundlagen ---
    int x = 10;
    int* p = &x;
    fmt::print("Wert von x: {}\n", x);
    fmt::print("Adresse von x: {}\n", fmt::ptr(&x));
    fmt::print("Wert auf den p zeigt (*p): {}\n", *p);
    fmt::print("Adresse, die in p gespeichert ist: {}\n", fmt::ptr(p));
    *p = 42;
    fmt::print("Nach Änderung über p:\n");
    fmt::print("Wert von x: {}\n", x);
    fmt::print("Wert auf den p zeigt (*p): {}\n", *p);

    // --- Teil 2: Dynamische Speicherverwaltung ---
    double* d = new double(3.1415);
    fmt::print("\nDynamisch reservierter Wert: {}\n", *d);
    fmt::print("Adresse von d: {}\n", fmt::ptr(d));
    delete d;

    // --- Teil 3: Funktionen mit Zeigern ---
    auto changeValueByParameter = [](int value) {
        value = 99;
        fmt::print("[changeValueByParameter] Neuer Wert: {}\n", value);
    };

    auto changeValueByPointer = [](int* ptr) {
        if (ptr) {
            *ptr = 77;
            fmt::print("[changeValueByPointer] Neuer Wert: {}\n", *ptr);
        }
    };

    int y = 5;
    fmt::print("\nVor changeValueByParameter: y = {}\n", y);
    changeValueByParameter(y);
    fmt::print("Nach changeValueByParameter: y = {}\n", y);

    fmt::print("\nVor changeValueByPointer: y = {}\n", y);
    changeValueByPointer(&y);
    fmt::print("Nach changeValueByPointer: y = {}\n", y);

    return 0; /* exit gracefully*/
}
