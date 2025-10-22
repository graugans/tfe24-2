#include <fmt/chrono.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

#include "CLI/CLI.hpp"
#include "config.h"

std::vector<int> generate_random_vector(std::size_t count){
    std::vector<int> numbers(count);
    std::random_device rd;   // liefert "echte" Zufallsquelle
    std::mt19937 gen(rd());  // Mersenne Twister Generator
    std::uniform_int_distribution<> dist(1, 100); // Zahlenbereich 1–100

    std::generate(numbers.begin(), numbers.end(), [&]() { return dist(gen); });
    return numbers;
}



void print_vector(const std::vector<int>& vec, const std::string& label) {
    fmt::print("{}: {}\n", label, vec);

}

auto main(int argc, char **argv) -> int
{
    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{PROJECT_NAME};
    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", app.get_name());

    /* INSERT YOUR CODE HERE */
    int count =57;
    app.add_option("-c,--count",count, "Anzahl der Elemente (Standard: 20)");

    std::cout<<"Zähle:"<<count<<std::endl;

    auto numbers = generate_random_vector(count);

    print_vector(numbers, "Vector Caption");
    auto start = std::chrono::system_clock::now();

    /* do some work */
    std::sort(numbers.begin(), numbers.end());
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);



    print_vector(numbers, "Sortiert");

    fmt::print("Sortierzeit: {} us\n", elapsed.count());

    return 0; /* exit gracefully*/
}
