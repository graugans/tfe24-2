#pragma once

#include <cmath>
#include <fmt/format.h>

class Point {
public:
    int x;
    int y;

    Point() : x(0), y(0) {}
    Point(int x_, int y_) : x(x_), y(y_) {}

    void move(int dx, int dy) { x += dx; y += dy; }
    void print() const { fmt::print("({}, {})\n", x, y); }

    double distance_to(const Point &other) const {
        const double dx = static_cast<double>(x - other.x);
        const double dy = static_cast<double>(y - other.y);
        return std::sqrt(dx * dx + dy * dy);
    }
};
