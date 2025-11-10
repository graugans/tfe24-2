#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"

#include "point.hpp"


int main()
{
    Point p1;     // Erzeugen eines Punktes (2, 3)
    p1.set(2,3);
    p1.print();         // Ausgabe: (2, 3)

    p1.move(1, -1);     // Verschiebe um (1, -1)
    p1.print();         // Ausgabe: (3, 2)

    Point p2;           // Standardkonstruktor -> (0, 0)
    p2.print();         // Ausgabe: (0, 0)

    return 0;
}
