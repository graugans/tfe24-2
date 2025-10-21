#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"

int globalVar = 1;


void foo() { 
    fmt::print("Hello from foo!\\n"); 
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
    //Variabeln ab hier:
    int localVar = 2;
    int* heapVar = new int(3);

    //code ab hier

    fmt::print("Wert der globalen Variable: {}\n", globalVar);
    fmt::print("Wert der lokalen Variable: {}\n", localVar);
    fmt::print("Adresse der dynamischen Variable: {}\n", fmt::ptr(heapVar));
    fmt::print("Wert der dynamischen Variable: {}\n", *heapVar);
     
    delete(heapVar);

    fmt::print("Adresse von foo: {}\\n", fmt::ptr(&foo));





    return 0; /* exit gracefully*/
}
