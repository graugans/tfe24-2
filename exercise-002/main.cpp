#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"


// --- Teil 1: Globale Variable (Data-Segment) ---
int globalVar = 1; // Globale Variable

// --- Teil 4: Funktion (Code-Segment) ---
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

    /* INSERT YOUR CODE HERE */



    fmt::print("--- Speichersegmente in C++ ---\n\n");

    // --- Teil 1: Data-Segment ---
    fmt::print("[Data-Segment] globalVar = {}, Adresse = {}\n", globalVar, fmt::ptr(&globalVar));

    // --- Teil 2: Stack ---
    int localVar = 2;
    fmt::print("[Stack]        localVar = {}, Adresse = {}\n", localVar, fmt::ptr(&localVar));

    // --- Teil 3: Heap ---
    int* heapVar = new int(3);
    fmt::print("[Heap]         *heapVar = {}, Adresse von heapVar (Zeiger selbst) = {}\n", *heapVar, fmt::ptr(heapVar));
    delete heapVar; // Speicher wieder freigeben

    // --- Teil 4: Code-Segment ---
    fmt::print("[Code]         Adresse von foo = {}\n\n", fmt::ptr(&foo));

    // --- Zusatz: Fazit ---
    fmt::print("--- Fazit ---\n");
    fmt::print("Globale Variablen liegen im Data-Segment.\n");
    fmt::print("Lokale Variablen liegen auf dem Stack.\n");
    fmt::print("Dynamisch erzeugte Variablen liegen im Heap und müssen mit delete freigegeben werden.\n");
    fmt::print("Funktionen (Code) liegen im Code-Segment.\n\n");
    fmt::print("Referenzen verweisen direkt auf Speicherstellen (wie Aliasse).\n");
    fmt::print("Zeiger speichern Adressen und ermöglichen Zugriff auf Stack-, Heap- oder globale Daten.\n");
    fmt::print("Wichtig: Heap-Variablen bleiben bestehen, bis sie gelöscht werden – Stack-Variablen verschwinden am Ende ihrer Gültigkeit.\n");

    return 0; /* exit gracefully*/
}
