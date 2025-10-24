#pragma once

#include <fmt/core.h>
#include "point.hpp"

// fmt formatter specialization for Point<T>
namespace fmt {
template <typename T>
struct formatter<Point<T>> : formatter<std::string_view> {
    template <typename FormatContext>
    auto format(const Point<T> &p, FormatContext &ctx) const {
        return fmt::format_to(ctx.out(), "({}, {})", p.x, p.y);
    }
};
} // namespace fmt
