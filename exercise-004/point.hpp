/*#ifndef POINT_HPP
#define POINT_HPP

class Point {

    public:
    Point();
    Point(double x, double y);
    ~Point(); 
    private:
    double
    double
};

#endif //*/

#ifndef POINT_HPP
#define POINT_HPP

#include <fmt/core.h>

class Point {
private:
    int x;
    int y;

public:
    // Standardkonstruktor
    Point();

    // Konstruktor mit Parametern
    Point(int xVal, int yVal);

    // Verschiebt den Punkt
    void move(int dx, int dy);

    // Gibt die Koordinaten aus
    void print() const;
};

#endif
