#include <fmt/chrono.h>
#include <fmt/format.h>

#include "config.h"

auto main(int argc, char **argv) -> int
{

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", tfe24::PROJECT_NAME);
 
    int x = 10;
    int *p = &x;
    fmt::print("Das ist die Addresse {}\n", fmt::ptr(&x));
    fmt::print("Addresse von x: {}, Addresse von x: {} \n", x, fmt::ptr(&x));
    *p = 42;
    fmt::print("Addresse von x: {}, Addresse von x: {} \n", x, fmt::ptr(&x));

    //Teil 2
    double *z = new double(3.1415);
    fmt::print("Addresse von z: {}, Addresse von z: {} \n", x, fmt::ptr(&z));
    delete z;


    return 0; /* exit gracefully*/
}
