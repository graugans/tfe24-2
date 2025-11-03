#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"

#include <algorithm> /* needed for the std::sort */
#include <random>

int DEFAULT_VECTOR_LENGTH = 20;


int main(int argc, char** argv) 
{
// Teil 1 der Aufgabe
    CLI::App app{"app, that can take a positive even integer as an inline input"};
    argv = app.ensure_utf8(argv);
    int vector_length = DEFAULT_VECTOR_LENGTH;
    app.add_option("-c,--count", vector_length, "Absolute quantity of numbers in the vector");
    try 
    {
    app.parse(argc, argv);
    } 
    catch (const CLI::ParseError &e) 
    {
    return app.exit(e);
    }
    fmt::print("vector length: {}\n", vector_length);

// Teil 2 der Aufgabe
    std::vector<int> random_vec;
    // Zufallsgenerator
    std::random_device random_seed;
    std::mt19937 generator(random_seed());
    std::uniform_int_distribution dis(1, 100);
    // for-Schleife für Generation der Zufallszahlen
    for (int iterator = 0; iterator < vector_length; iterator++) 
    {
        int random_number = dis(generator);
        random_vec.push_back(random_number);
    } 
    return 0;
}


