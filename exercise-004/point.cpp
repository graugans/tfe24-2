#include "point.hpp"

// Standardkonstruktor: setzt x = 0, y = 0
Point::Point() : x(0), y(0) {}

// Konstruktor mit Parametern
Point::Point(int xVal, int yVal) : x(xVal), y(yVal) {}

// Methode zum Verschieben
void Point::move(int dx, int dy) {
    x += dx;
    y += dy;
}

// Methode zur Ausgabe mit fmt::print
void Point::print() const {
    fmt::print("({0}, {1})\n", x, y);
}
