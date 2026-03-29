#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"

void foo()
{
    fmt::print("Hello from foo!\n");
    return;
}
// Teil 1: Globale Variablen (Data-Segment)
int globalVar = 1;

int main() 
{
    fmt::print("globalVar = {}\n", globalVar);

// Teil 2: Lokale Variablen (Stack)
    int localVar = 2;
    fmt::print("localVar = {}\n", localVar);

// Teil 3: Dynamisch allozierte Variablen (Heap)
    int *heapVar = new int(3);
    fmt::print("heapVar = {}\n", *heapVar);
    delete heapVar;

// Teil 4: Funktionen (Code-Segment)
    fmt::print("Adresse von foo: {}\n", fmt::ptr(&foo));

    return 1;
}
