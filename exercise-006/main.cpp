#include <fmt/format.h>

#include "config.h"
#include "point/point.hpp"

class Point2 {
    public:
        Point2(double x, double y) : x{x}, y{y} {
            fmt::print("Point2 Konstruktor({}, {})\n", x, y);
        }
        void print() const {
            fmt::print("Point2({}, {})\n", x, y);
        }
    private:
        double x;
        double y;
};


auto main(int argc, char **argv) -> int
{
    Point<double> p1(2, 3);     // Erzeugen eines Punktes (2, 3)
    p1.print();         // Ausgabe: (2, 3)

    p1.move(1, -1);     // Verschiebe um (1, -1)
    p1.print();         // Ausgabe: (3, 2)

    Point<double> p2;           // Standardkonstruktor -> (0, 0)
    p2.print();         // Ausgabe: (0, 0)

    Point<int> p3{2,3};
    p3.print();         // Ausgabe: (0, 0)


    fmt::println("Distance between p1 and p2: {}", p1.distance_to(p2));
    //fmt::println("Distance between p2 and p3: {}", p2.distance_to(p3)); // Sollte nicht kompilieren

    fmt::println("Print using fmt lib: p1 = {}", p1);
    fmt::println("Print using fmt lib: p2 = {}", p2);
    Point<double> p4{2.5,3.6};
    fmt::println("Print using fmt lib: p3 = {}", p4);

    // Automatische Typ Deduktion
    Point p5{2.5,3.6};
    fmt::println("Print using fmt lib: p3 = {}", p5);

    Point p6{2,3};
    fmt::println("Print using fmt lib: p3 = {}", p6);

    // Templates erfordern konsistente Typen
    // Testen Sie die folgende Zeile, um einen Kompilierungsfehler zu sehen
    // Was passiert im Falle der Aufgabe 5 ohne Templates?
    //Point p7{2,3.0f};
    //fmt::println("Print using fmt lib: p3 = {}", p7);
    Point2 p7{2,3.0f};
    // warum geht das folgende nicht?
    //fmt::println("Print using fmt lib: p3 = {}", p7);
    p7.print();

    Point<double> p8{4,6};
    p8*2;
    fmt::println("Print using fmt lib: p8 = {}", p8);   

    Point p9 = p8;
    fmt::println("Print using fmt lib: p9 = {}", p9);
    fmt::println("Print using fmt lib: p9 = {}", p9*2.2);
    return 0; /* exit gracefully*/
}
