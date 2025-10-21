#include <fmt/chrono.h>
#include <fmt/format.h>
#include <vector>
#include <random>

#include "CLI/CLI.hpp"
#include "config.h"

// Function to print all elements in a vector<int> using {fmt}
void print_vector(const std::vector<int> &vec) {
    fmt::print("Random values: ");
    for (const auto &val : vec) {
        fmt::print("{} ", val);
    }
    fmt::print("\n");
}

auto main(int argc, char **argv) -> int
{
    CLI::App app{PROJECT_NAME};

    int count = 20;
    app.add_option("-c,--count", count, "Count parameter, default 20")->default_val("20");

    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    fmt::print("Hello, {}!\n", app.get_name());
    fmt::print("Parameter count: {}\n", count);

    // Initialize random number generation machinery
    std::random_device rd;  // Seed source
    std::mt19937 gen(rd()); // Mersenne Twister PRNG
    std::uniform_int_distribution<> dis(1, 100); // Uniform dist 1-100

    // Create vector with size `count`
    std::vector<int> random_values(count);

    // Fill vector with random ints in range 1-100
    for(auto &val : random_values) {
        val = dis(gen);
    }

    // Output the random values using the print_vector function
    print_vector(random_values);

    return 0;
}
