#ifndef POINT_HPP
#define POINT_HPP

#include <fmt/core.h>

// --- Task: Implement the Point class ---
class Point
{
public:
    int x;
    int y;

    // Default constructor
    Point() : x(0), y(0) {}

    // Constructor with initialization
    Point(int x_, int y_) : x(x_), y(y_) {}

    void move(int dx, int dy)
    {
        x += dx;
        y += dy;
    }

    void print() const
    {
        fmt::print("({0}, {1})\n", x, y);
    }

    double distance_to(const Point &other) const
    {
        double dx = static_cast<double>(x - other.x);
        double dy = static_cast<double>(y - other.y);
        return std::sqrt(dx * dx + dy * dy);
    }
};

#endif