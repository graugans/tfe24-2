#include "point.hpp"
#include <fmt/format.h>


// Methoden (Getter / Setter)
void Point::set(int xx, int yy)
{
    Point::x = xx;
    Point::y = yy;
    return;
}

void Point::move(int dx, int dy)
{
    Point::x += dx;
    Point::y += dy;
    return;
};

void Point::print()const
{
    fmt::print("({},", Point::x);
    fmt::print("{})\n", Point::y);
    return;
};
