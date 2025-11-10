#include "point.hpp"
#include <fmt/format.h>
#include <cstdio>

void Point::print() const
{
    fmt::print("({},", px);
    fmt::print("{})\n", py);
    return;
};
