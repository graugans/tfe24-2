#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"

auto main(int argc, char **argv) -> int
{
    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{PROJECT_NAME};

    // Define an integer variable for the count parameter, default to 20
    int count = 20;
    // Add the --count / -c option for the count parameter with description and default value
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

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */

    
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

    // Optional: output the random values (comment out if undesired)
    fmt::print("Random values: ");
    for(const auto &val : random_values){
        fmt::print("{} ", val);
    }
    fmt::print("\n");

    return 0; /* exit gracefully*/
}