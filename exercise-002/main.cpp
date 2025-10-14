// Teil 1: Globale Variable (Data-Segment)
int globalVar = 1;

// Teil 4: Funktion (Code-Segment)
void foo() { fmt::print("Hello from foo!\n"); }

#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"

// Teil 1: Globale Variable (Data-Segment)
int globalVar = 1;

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


    // Teil 1: Globale Variable (Data-Segment)
    fmt::print("Teil 1: globalVar = {}, Adresse = {}\n", globalVar, fmt::ptr(&globalVar));

    // Teil 2: Lokale Variable (Stack)
    int localVar = 2;
    fmt::print("Teil 2: localVar = {}, Adresse = {}\n", localVar, fmt::ptr(&localVar));

    // Teil 3: Dynamisch allozierte Variable (Heap)
    int* heapVar = new int(3);
    fmt::print("Teil 3: *heapVar = {}, Adresse = {}\n", *heapVar, fmt::ptr(heapVar));
    delete heapVar;

    // Teil 4: Funktion (Code-Segment)
    fmt::print("Teil 4: Adresse von foo = {}\n", fmt::ptr(reinterpret_cast<void*>(&foo)));
    foo();

    // Fazit
    /*
    Fazit:
    - Globale Variablen werden im Data-Segment gespeichert und sind während der gesamten Programmlaufzeit verfügbar.
    - Lokale Variablen liegen auf dem Stack und sind nur innerhalb ihres Gültigkeitsbereichs sichtbar.
    - Dynamisch allozierte Variablen werden im Heap angelegt und müssen manuell freigegeben werden.
    - Funktionen liegen im Code-Segment.
    - Die Unterscheidung zwischen Stack und Heap ist wichtig für Speicherverwaltung und Lebensdauer von Variablen.
    - Referenzen und Zeiger ermöglichen den Zugriff auf Speicheradressen und sind essenziell für dynamische Speicherverwaltung und effiziente Programmierung.
    */

    return 0; /* exit gracefully*/
}
