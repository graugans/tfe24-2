#include <fmt/chrono.h>
#include <fmt/format.h>

#include <nlohmann/json.hpp>

#include "CLI/CLI.hpp"
#include "config.h"
#include "point.hpp"

// for convenience
using json = nlohmann::json;

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

    /* Example usage of Point<T> template class */
    fmt::print("\n--- Point<T> Template Examples ---\n");

    // Example with int
    Point<int> p1{2, 3};
    Point<int> p2{5, 7};
    fmt::print("p1 = {}\n", p1);
    fmt::print("p2 = {}\n", p2);
    fmt::print("Distance from p1 to p2: {}\n", p1.distance_to(p2));

    // Example with double
    Point<double> p3{1.5, 2.5};
    fmt::print("p3 = {}\n", p3);
    p3.move(0.5, 1.0);
    fmt::print("p3 after move(0.5, 1.0) = {}\n", p3);

    // Example with float
    Point<float> p4{0.0f, 0.0f};
    Point<float> p5{3.0f, 4.0f};
    fmt::print("p4 = {}\n", p4);
    fmt::print("p5 = {}\n", p5);
    fmt::print("Distance from p4 to p5: {}\n", p4.distance_to(p5));

    return 0; /* exit gracefully*/
}

