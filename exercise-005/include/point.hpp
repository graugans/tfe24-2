#pragma once

#include <cmath>

struct Point {
    int x;
    int y;

    Point(): x(0), y(0) {}
    Point(int x_, int y_): x(x_), y(y_) {}

    void move(int dx, int dy) noexcept {
        x += dx;
        y += dy;
    }

    double distance_to(const Point& other) const noexcept {
        double dx = static_cast<double>(x) - static_cast<double>(other.x);
        double dy = static_cast<double>(y) - static_cast<double>(other.y);
        return std::sqrt(dx * dx + dy * dy);
    }
};
