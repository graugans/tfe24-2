#include <fmt/chrono.h>
#include <fmt/format.h>

#include "config.h"

void changeValueByParameter(int value);
void changeValueByPointer(int* ptr);

auto main(int argc, char **argv) -> int
{

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello world, {}!\n", tfe24::PROJECT_NAME);

    /* INSERT YOUR CODE HERE */
    fmt::print("\n\nPart 1 \n");
    int x = 10;
    int* p = &x;

    fmt::print("Value of x: {}", x);
    fmt::print("\nAddress of x: {}\n", fmt::ptr(p));

    *p = 42;
    fmt::print("New value of x: {}\n", x);
    fmt::print("Address of new x: {}\n", fmt::ptr(p));

    fmt::print("\n\nPart 2 \n");
    double* d = new double(3.1415);

    fmt::print("Value of d: {}\n", *d);
    fmt::print("Address of d: {}\n", fmt::ptr(d));

    delete d;

    fmt::print("\n\nPart 3.1: Change by Parameter \n");
    int value = 200;
    fmt::print("Value before function call: {}\n", value);
    changeValueByParameter(value);
    fmt::print("Value after function call: {}\n", value);

    fmt::print("\n\nPart 3.2: Change by Pointer \n");
    int* ptr = &value;
    fmt::print("Value before function call: {}\n", value);
    changeValueByPointer(ptr);
    fmt::print("Value after function call: {}\n", value);

    return 0; /* exit gracefully*/
}

 void changeValueByParameter(int value)
 {
    value = 99;
}

void changeValueByPointer(int* ptr)
{
    *ptr = 99;
}