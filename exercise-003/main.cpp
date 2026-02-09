#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"

#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

/**
 * Print the contents of a vector
 */
auto print_vector(const std::vector<int>& vec) -> void
{
    fmt::print("Vector: ");
    for (const auto& value : vec) {
        fmt::print("{} ", value);
    }
    fmt::print("\n");
}

auto main(int argc, char **argv) -> int
{
    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{PROJECT_NAME};
    
    // Add count parameter
    int count = 20;
    app.add_option("-c,--count", count, "Number of random values to generate (default: 20)");
    
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
    fmt::print("Generating {} random values...\n", count);

    // Create vector with random values (1-100)
    std::vector<int> numbers;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    
    for (int i = 0; i < count; ++i) {
        numbers.push_back(dis(gen));
    }
    
    // Print unsorted vector
    fmt::print("\nUnsorted vector:\n");
    print_vector(numbers);
    
    // Measure sorting time
    auto start = std::chrono::system_clock::now();
    std::sort(numbers.begin(), numbers.end());
    auto end = std::chrono::system_clock::now();
    
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // Print sorted vector
    fmt::print("\nSorted vector:\n");
    print_vector(numbers);
    
    // Print elapsed time
    fmt::print("\nSorting time: {}\n", elapsed);

    return 0; /* exit gracefully*/
}
