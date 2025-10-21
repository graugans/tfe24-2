#include <fmt/chrono.h>
#include <fmt/format.h>
#include <vector>
#include <random>
#include <algorithm>  // std::sort
#include <chrono>     // Zeitmessung
#include <string>
#include <iostream>
#include "CLI/CLI.hpp"
#include "config.h"

// Funktion, die einen Vektor ausgibt, Parameter als const ref
void print_vector(const std::vector<int> &vec) {
    fmt::print("Values: ");
    for (const auto &val : vec) {
        fmt::print("{} ", val);
    }
    fmt::print("\n");
}

auto main(int argc, char **argv) -> int
{
    CLI::App app{PROJECT_NAME};

    int count = 20;  // Defaultwert 20, wird ggf. überschrieben
    app.add_option("-c,--count", count, "Count parameter, default 20");

    try {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        return app.exit(e);
    }

    // Interaktive Abfrage, falls kein -c oder --count gesetzt wurde
    if (!app.count("-c") && !app.count("--count")) {
        fmt::print("Please enter the count value (default 20): ");
        std::string input;
        std::getline(std::cin, input);
        if (!input.empty()) {
            try {
                count = std::stoi(input);
            } catch (...) {
                fmt::print("Invalid input, using default 20\n");
                count = 20;
            }
        } else {
            count = 20;
        }
    }

    fmt::print("Hello, {}!\n", app.get_name());
    fmt::print("Parameter count: {}\n", count);

    // Zufallsgenerator initialisieren
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    // Vektor mit "count" Elementen anlegen und mit Zufallszahlen füllen
    std::vector<int> random_values(count);
    for (auto &val : random_values) {
        val = dis(gen);
    }

    fmt::print("Unsorted ");
    print_vector(random_values);

    // Zeitmessung vor und nach Sortierung
    auto start = std::chrono::system_clock::now();
    std::sort(random_values.begin(), random_values.end());
    auto end = std::chrono::system_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    fmt::print("Sorted ");
    print_vector(random_values);

    fmt::print("Sorting took {} milliseconds\n", elapsed.count());

    return 0;
}
