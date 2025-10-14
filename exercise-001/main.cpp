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


    // Teil 1: Grundlagen Referenzen
    int x = 10;
    int& r = x;
    fmt::print("Teil 1: x = {}, r = {}\n", x, r);
    r = 42;
    fmt::print("Teil 1 nach Änderung: x = {}, r = {}\n", x, r);

    // Teil 2: Funktionen mit Referenzen
    auto changeValueByParameter = [](int value) {
        value = 99;
        fmt::print("In changeValueByParameter: value = {}\n", value);
    };
    auto changeValueByReference = [](int& ref) {
        ref = 77;
        fmt::print("In changeValueByReference: ref = {}\n", ref);
    };

    // Teil 3: Vergleich
    int y = 5;
    fmt::print("Teil 3: Vor changeValueByParameter: y = {}\n", y);
    changeValueByParameter(y);
    fmt::print("Teil 3: Nach changeValueByParameter: y = {}\n", y);

    fmt::print("Teil 3: Vor changeValueByReference: y = {}\n", y);
    changeValueByReference(y);
    fmt::print("Teil 3: Nach changeValueByReference: y = {}\n", y);

    return 0; /* exit gracefully*/
}
