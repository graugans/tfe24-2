#include <fmt/chrono.h>
#include <fmt/format.h>

#include <nlohmann/json.hpp>

#include "CLI/CLI.hpp"
#include "config.h"

// for convenience
using json = nlohmann::json;

#include "include/point.hpp"
#include "include/point_fmt.hpp"

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

    // optional operators
    Point operator+(const Point &rhs) const { return Point(x + rhs.x, y + rhs.y); }
    Point operator-(const Point &rhs) const { return Point(x - rhs.x, y - rhs.y); }

    template <typename U>
    auto operator*(U s) const -> Point<std::common_type_t<T, U>> {
        using R = std::common_type_t<T, U>;
        return Point<R>(static_cast<R>(x) * static_cast<R>(s), static_cast<R>(y) * static_cast<R>(s));
    }
};

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

auto main(int argc, char **argv) -> int
{
    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{PROJECT_NAME};
    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", app.get_name());

    // Example usage
    Point<int> pi{2, 3};
    fmt::print("Point<int> pi = {}\n", pi);
    pi.move(1, -1);
    fmt::print("After move: {}\n", pi);

    Point<double> pd{0.5, -1.25};
    pd.move(0.25, 0.75);
    fmt::print("Point<double> pd = {}\n", pd);

    fmt::print("Distance pi <-> pd = {}\n", pi.distance_to(pd));

    return 0; /* exit gracefully*/
}
