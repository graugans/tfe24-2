#include <fmt/chrono.h>
#include <fmt/format.h>
#include <iostream>

#include "config.h"



void changeValueByPointer(int* ptr){
*ptr = 77;
fmt::print("Wert über Pointer ptr (*ptr): {}\n", *ptr);
}

void changeValueByParameter(int value) {
    value = 99;  // Wert innerhalb der Funktion ändern
    std::cout << "[Funktion] Neuer Wert von value: " << value << std::endl;
}



auto main(int argc, char **argv) -> int
{


    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello world, {}!\n", tfe24::PROJECT_NAME);

    /* INSERT YOUR CODE HERE */

    int x = 10;
    int *p = &x;

    fmt::print("Wert von x: {}\n", x);              // Gibt 10 aus
    fmt::print("Pointer-Adresse: {}\n", fmt::ptr(&x));         // Gibt Adresse von x aus
    fmt::print("Wert über Pointer p (*p): {}\n", *p); // Gibt ebenfalls 10 aus
    fmt::print("Pointer-Adresse: {}\n", fmt::ptr(p));    // Zeigt dieselbe Adresse wie &x
    *p = 42;                                          // Ändert x auf 42
   fmt::print("Neuer Wert über *p: {}\n", *p);       // Gibt 42 aus

    double*o = new double;
    *o = 3.1415;
    fmt::print("Pointer-Adresse: {}\n", fmt::ptr(o));
    fmt::print("Wert über Pointer o (*o): {}\n", *o);
    delete o;

    int firstvar = 57;
    int y = 5;
    int *ptr = &firstvar;
    int *po = &y;

    fmt::print("Wert meiner Ursprungsvariable: {}\n", firstvar);

    changeValueByParameter(firstvar);
    changeValueByPointer(ptr);
    changeValueByParameter(y);
    changeValueByPointer(po);

    return 0; /* exit gracefully*/
}
