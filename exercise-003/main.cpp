#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"

#include <algorithm> /* needed for the std::sort */
#include <random>


int main(int argc, char** argv) 
{
    CLI::App app{"app, that can take a positive even integer as an inline input"};
    argv = app.ensure_utf8(argv);

    std::string filename = "default";
    app.add_option("-f,--file", filename, "A help string");

    try 
    {
    app.parse(argc, argv);
    } 
    catch (const CLI::ParseError &e) 
    {
    return app.exit(e);
    }
    return 0;
}


