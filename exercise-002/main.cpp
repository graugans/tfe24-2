#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"

// Part 1: Global Variable (Data Segment)
int globalVar = 1;

// Part 4: Function (Code Segment)
void foo() {
    fmt::print("Hello from foo!\n");
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

    // Part 1: Global Variable
    fmt::print("Global variable value: {}\n", globalVar);
    fmt::print("Global variable address: {}\n\n", fmt::ptr(&globalVar));

    // Part 2: Local Variable (Stack)
    int localVar = 2;
    fmt::print("Local variable value: {}\n", localVar);
    fmt::print("Local variable address: {}\n\n", fmt::ptr(&localVar));

    // Part 3: Dynamic Variable (Heap)
    int* heapVar = new int(3);
    fmt::print("Heap variable value: {}\n", *heapVar);
    fmt::print("Heap variable address: {}\n\n", fmt::ptr(heapVar));
    delete heapVar;

    // Part 4: Function (Code Segment)
    fmt::print("Address of foo: {}\n\n", fmt::ptr(&foo));

    // Conclusion
    fmt::print("Conclusion:\n");
    fmt::print("- Global/static variables are stored in the data segment.\n");
    fmt::print("- Local variables live on the stack.\n");
    fmt::print("- Dynamically allocated variables live on the heap.\n");
    fmt::print("- Functions reside in the code segment.\n");
    fmt::print("- Stack vs heap matters for lifetime, performance, and memory management.\n");
    fmt::print("- Pointers and references allow direct access to where variables are stored.\n");

    return 0; /* exit gracefully*/
}
