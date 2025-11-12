#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"
#include "myvector.hpp"

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

    
    using tfe24::myvector;

    // simple smoke test
    {
        myvector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        fmt::print("v.size() = {}\n", v.size());
        fmt::print("v[1] = {}\n", v[1]);
        v.resize(6);
        fmt::print("after resize v.size() = {} capacity = {}\n", v.size(), v.capacity());
        v.clear();
        fmt::print("after clear v.size() = {}\n", v.size());
    }

    fmt::println("Hello exercise number 10: myvector demo complete");

    return 0; /* exit gracefully*/
}
