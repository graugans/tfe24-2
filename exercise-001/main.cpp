#include <fmt/chrono.h>
#include <fmt/format.h>
#include "config.h"

// Part 1: Grundlagen Referenzen
void part1() {
    int x = 10;          // Declare int variable x with value 10
    int& r = x;          // Declare reference r to x
    
    fmt::print("Part 1\n");
    fmt::print("x = {}\n", x);    // Print value of x
    fmt::print("r = {}\n", r);    // Print value of r

    r = 42;                      // Change value of x using the reference r

    fmt::print("x = {}\n", x);    // Print updated value of x
    fmt::print("r = {}\n", r);    // Print updated value of r
}

// Part 2: Funktionen mit Referenzen
void changeValueByParameter(int value) {
    value = 99;
    fmt::print("Inside changeValueByParameter: value = {}\n", value);
}

void changeValueByReference(int& ref) {
    ref = 77;
    fmt::print("Inside changeValueByReference: ref = {}\n", ref);
}

void part2() {
    int x = 10;
    
    fmt::print("\nPart 2\n");
    changeValueByParameter(x);
    fmt::print("After changeValueByParameter: x = {}\n", x);

    changeValueByReference(x);
    fmt::print("After changeValueByReference: x = {}\n", x);
}

// Part 3: Vergleich
void part3() {
    int y = 5;

    fmt::print("\nPart 3\n");
    fmt::print("Before changeValueByParameter: y = {}\n", y);
    changeValueByParameter(y);
    fmt::print("After changeValueByParameter: y = {}\n", y);

    fmt::print("Before changeValueByReference: y = {}\n", y);
    changeValueByReference(y);
    fmt::print("After changeValueByReference: y = {}\n", y);
}

auto main(int argc, char **argv) -> int
{
    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", tfe24::PROJECT_NAME);

    // Part 1
    part1();

    // Part 2
    part2();

    // Part 3
    part3();

    return 0; /* exit gracefully*/
}
