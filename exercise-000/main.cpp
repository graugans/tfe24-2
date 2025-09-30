#include <fmt/chrono.h>
#include <fmt/format.h>

#include "config.h"

// Function to change value by parameter
void changeValueByParameter(int value) {
    value = 77;
}

// Function to change value by pointer
void changeValueByPointer(int* ptr) {
    if (ptr) {
        *ptr = 77;
    }
}

auto main(int argc, char **argv) -> int
{

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */

    fmt::print("Hello world, {}!\n", tfe24::PROJECT_NAME);


    //Part 1

    int x = 10; // Declare an integer variable x and initialize it with the value 10
    int* p = &x; // Declare a pointer variable p and initialize it with the address of x

    fmt::print("Value of x: {}\n", x); // Print the value of x
    fmt::print("Address of x: {}\n", fmt::ptr(&x)); // Print the address of x using fmt::ptr to format the pointer

    fmt::print("Value on which p points {}\n", *p); // Print the value pointed to by p (which is the value of x)
    fmt::print("Address saved in p: {}\n", fmt::ptr(p)); // Print the address stored in p using fmt::ptr

    *p = 42; // Change the value pointed to by p to 42, which also changes the value of x

    fmt::print("New Value of x: {}\n", x); // Print the new value of x
    fmt::print("New Value on which p points: {}\n", *p); // Print the new value pointed to by p (which is now 42)

    //Part 2

    double* d = new double{3.1415}; // Dynamically allocate memory for a double and initialize it with the value 3.1415
    fmt::print("Value of the double-Pointers: {}\n", *d); // Print the value pointed to by dptr
    fmt::print("Address of the double-Pointers: {}\n", fmt::ptr(d)); // Print the address stored in dptr using fmt::ptr

    delete d; // Deallocate the memory allocated for the double to prevent memory leaks
    d = nullptr; // Set dptr to nullptr to avoid dangling pointer

    //Part 3

    //Functions are declared outside of the main function
    int y = 123; // Declare an integer variable y and initialize it with the value 123
    fmt::print("\nVor changeValueByParameter: y = {}\n", y); // Print the value of y before calling the function
    changeValueByParameter(y); // Call the function to change the value by parameter
    fmt::print("Nach changeValueByParameter: y = {}\n", y); // Print the value of y after calling the function (should remain unchanged)

    fmt::print("\nVor changeValueByPointer: y = {}\n", y); // Print the value of y before calling the function
    changeValueByPointer(&y); // Call the function to change the value by pointer (pass the address of y)
    fmt::print("Nach changeValueByPointer: y = {}\n", y); // Print the value of y after calling the function (should be changed to 77)

    return 0; /* exit gracefully*/
}