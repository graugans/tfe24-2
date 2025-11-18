#include <fmt/chrono.h>
#include <fmt/format.h>

#include <nlohmann/json.hpp>

#include "CLI/CLI.hpp"
#include "config.h"

// for convenience
using json = nlohmann::json;
namespace fs = std::filesystem;

auto main(int argc, char** argv) -> int
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
    catch (const CLI::ParseError& e)
    {
        return app.exit(e);
    }

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", app.get_name());



    const auto path = fs::path{config::json_tests};

    std::ifstream in(path);
    if (!in.is_open())
    {
        fmt::print("Fehler: konnte JSON-Datei nicht öffnen: {}\n", path.string());
        return EXIT_FAILURE;
    }

    // gesamte Datei in einen String laden
    std::string text(std::istreambuf_iterator<char>{in}, std::istreambuf_iterator<char>{});

    // JSON parsen
    json doc = json::parse(text);

    return EXIT_SUCCESS; /* exit gracefully*/
}
