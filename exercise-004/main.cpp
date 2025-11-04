#include <fmt/chrono.h>
#include <fmt/format.h>

// Damit wir auf PROJECT_NAME zugreifen können
#include "config.h"

// Point-Klasse einbinden
#include "point.hpp"
// Durch den Include-Guard in point.hpp wird sichergestellt, 
// dass die Klasse Point nur einmal definiert wird
#include "point.hpp"

auto main(int argc, char **argv) -> int
{
    fmt::println("Hello, {}!", PROJECT_NAME);

    // Test des Standardkonstruktors und Destruktors
    {
        Point p; // Standardkonstruktor
    } // Destruktor wird hier aufgerufen

    Point p1(2, 3);     // Erzeugen eines Punktes (2, 3)
    p1.print();         // Ausgabe: (2, 3)

    p1.move(1, -1);     // Verschiebe um (1, -1)
    p1.print();         // Ausgabe: (3, 2)

    Point p2;           // Standardkonstruktor -> (0, 0)
    p2.print();         // Ausgabe: (0, 0)

    fmt::println("Distance between p1 and p2: {}", p1.distance_to(p2));

    return 0; /* exit gracefully*/
}
