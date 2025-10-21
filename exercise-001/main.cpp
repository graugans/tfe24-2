#include <fmt/chrono.h>
#include <fmt/format.h>

#include "config.h"



void changeValueByParameter(int value) {
    value = 99;  // Wert innerhalb der Funktion ändern
    fmt::print("Neuer Wert von value: {}\n", value);
}


void changeValueByReference(int &maurice){
maurice = 88;
fmt::print("Wert auf den Maurice zeigt: {}\n", maurice);
}

auto main(int argc, char **argv) -> int
{
    
    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", tfe24::PROJECT_NAME);

    /* INSERT YOUR CODE HERE */

    int x=10;
    int& r = x;
    fmt::print("Wert über die Referencevariable (r): {}\n", r);
    r = 42;
    fmt::print("Wert über die Referencevariable nach Wechsel (r): {}\n", r);

    int value = 75;
    int y = 5;
    

    changeValueByParameter (value);
    changeValueByReference(value);
    changeValueByParameter (y);
    changeValueByReference(y);

    return 0; /* exit gracefully*/
}
