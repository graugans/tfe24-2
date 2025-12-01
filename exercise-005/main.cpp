#include <fmt/chrono.h>
#include <fmt/format.h>


#include "config.h"
#include "point/point.hpp"




auto main(int argc, char **argv) -> int
{

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", PROJECT_NAME);

    {
        Point<double> p; // Standardkonstruktor
    } // Destruktor wird hier aufgerufen

    Point<double> p1(2, 3);     // Erzeugen eines Punktes (2, 3)
    p1.print();         // Ausgabe: (2, 3)

    p1.move(1, -1);     // Verschiebe um (1, -1)
    p1.print();         // Ausgabe: (3, 2)

    Point<double> p2;           // Standardkonstruktor -> (0, 0)
    p2.print();         // Ausgabe: (0, 0)

    fmt::println("Distance between p1 and p2: {}", p1.distance_to(p2));


    return 0; /* exit gracefully*/
}
