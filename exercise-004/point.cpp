#include "point.hpp"
#include <fmt/format.h>
#include <cstdio>

// Methoden (Getter)
int Point::x()
{
    return px;
}

int Point::y()
{
    return py;
}

// Methoden (Setter)
void Point::set(int x, int y)
{
    px = x;
    py = y;
    return;
}

void Point::move(int dx, int dy)
{
    px += dx;
    py += dy;
    return;
};

void Point::print() const
{
    fmt::print("({},", px);
    fmt::print("{})\n", py);
    return;
};
