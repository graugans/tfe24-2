#pragma once

#include <type_traits>
#include <cmath>
#include <utility>
#include <tuple>

// Generic Point<T> template (C++17-compatible)
template <typename T>
class Point {
    static_assert(std::is_arithmetic<T>::value, "Point<T>: T must be arithmetic");
public:
    T x{};
    T y{};

    Point() = default;
    Point(T x_, T y_) : x{x_}, y{y_} {}

    void move(T dx, T dy) { x += dx; y += dy; }

    template <typename U>
    auto distance_to(const Point<U> &other) const -> std::common_type_t<T, U, double> {
        using dist_t = std::common_type_t<T, U, double>;
        const dist_t dx = static_cast<dist_t>(x) - static_cast<dist_t>(other.x);
        const dist_t dy = static_cast<dist_t>(y) - static_cast<dist_t>(other.y);
        return std::hypot(dx, dy);
    }

    bool operator==(const Point &rhs) const { return x == rhs.x && y == rhs.y; }
    bool operator!=(const Point &rhs) const { return !(*this == rhs); }

    Point operator+(const Point &rhs) const { return Point(x + rhs.x, y + rhs.y); }
    Point operator-(const Point &rhs) const { return Point(x - rhs.x, y - rhs.y); }

    template <typename U>
    auto operator*(U s) const -> Point<std::common_type_t<T, U>> {
        using R = std::common_type_t<T, U>;
        return Point<R>(static_cast<R>(x) * static_cast<R>(s), static_cast<R>(y) * static_cast<R>(s));
    }
};
