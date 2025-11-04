// point.hpp
// Simple Point class used in tests for exercise-005
#pragma once

#include <cmath>

class Point {
public:
    int x;
    int y;

    // Default ctor
    Point() : x(0), y(0) {}

    // Parameter ctor
    Point(int x_, int y_) : x(x_), y(y_) {}

    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    double distance_to(const Point& other) const {
        double dx = static_cast<double>(x - other.x);
        double dy = static_cast<double>(y - other.y);
        return std::sqrt(dx*dx + dy*dy);
    }
};