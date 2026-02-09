#pragma once
#include <type_traits>
#include <cmath>

template <typename T>
class Point {
  static_assert(std::is_arithmetic_v<T>, "Point<T>: T must be arithmetic");

public:
  T x{};
  T y{};

  // Default constructor
  Point() = default;

  // Constructor with values
  Point(T x_, T y_) : x{x_}, y{y_} {}

  // Move the point by the given offsets
  void move(T dx, T dy) {
    x += dx;
    y += dy;
  }

  // Calculate distance to another point
  using dist_t = std::common_type_t<T, double>;
  auto distance_to(const Point& other) const -> dist_t {
    const auto dx = static_cast<dist_t>(x) - static_cast<dist_t>(other.x);
    const auto dy = static_cast<dist_t>(y) - static_cast<dist_t>(other.y);
    return std::hypot(dx, dy);
  }

  // Comparison operators
  bool operator==(const Point& rhs) const {
    return x == rhs.x && y == rhs.y;
  }

  bool operator!=(const Point& rhs) const {
    return !(*this == rhs);
  }
};

// fmt formatter specialization - must be after class definition
#include <fmt/core.h>

template <typename T>
struct fmt::formatter<Point<T>> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx) {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const Point<T>& p, FormatContext& ctx) const {
    return fmt::format_to(ctx.out(), "({}, {})", p.x, p.y);
  }
};
