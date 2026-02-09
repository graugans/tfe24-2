#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"

// Teil 1: Globale Variable (Data-Segment)
int globalVar = 1;

// Teil 4: Funktion (Code-Segment)
void foo()
{
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

    fmt::print("\n=== Speichersegmente in C++ ===\n\n");

    // Teil 1: Globale Variable (Data-Segment)
    fmt::print("Teil 1: Globale Variable (Data-Segment)\n");
    fmt::print("  globalVar = {}\n", globalVar);
    fmt::print("  Adresse: {:p}\n\n", fmt::ptr(&globalVar));

    // Teil 2: Lokale Variable (Stack)
    fmt::print("Teil 2: Lokale Variable (Stack)\n");
    int localVar = 2;
    fmt::print("  localVar = {}\n", localVar);
    fmt::print("  Adresse: {:p}\n\n", fmt::ptr(&localVar));

    // Teil 3: Dynamisch allozierte Variable (Heap)
    fmt::print("Teil 3: Dynamisch allozierte Variable (Heap)\n");
    int* heapVar = new int(3);
    fmt::print("  *heapVar = {}\n", *heapVar);
    fmt::print("  Adresse: {:p}\n", fmt::ptr(heapVar));
    delete heapVar;
    fmt::print("  (Speicher wurde freigegeben)\n\n");

    // Teil 4: Funktion (Code-Segment)
    fmt::print("Teil 4: Funktion (Code-Segment)\n");
    fmt::print("  Adresse von foo: {:p}\n", fmt::ptr(&foo));
    foo();

    fmt::print("\n=== Fazit ===\n");
    fmt::print("- Globale Variablen werden im Data-Segment gespeichert\n");
    fmt::print("- Lokale Variablen werden auf dem Stack angelegt\n");
    fmt::print("- Dynamisch allozierte Variablen liegen im Heap\n");
    fmt::print("- Funktionen befinden sich im Code-Segment\n");
    fmt::print("\nWarum wichtig:\n");
    fmt::print("- Stack ist schnell, aber begrenzt und wird automatisch freigegeben\n");
    fmt::print("- Heap ist größer, muss aber manuell freigegeben werden\n");
    fmt::print("- Zeiger ermöglichen flexible Verwaltung und Weitergabe von Adressen\n");

    return 0; /* exit gracefully*/
}
