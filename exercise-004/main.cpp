#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"

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

    // --- Point class definition ---
    class Point {
    public:
        int x;
        int y;

        // default constructor
        Point() : x(0), y(0) {}

        // constructor with parameters
        Point(int x_, int y_) : x(x_), y(y_) {}

        // move the point
        void move(int dx, int dy) { x += dx; y += dy; }

        // print coordinates
        void print() const { fmt::print("({}, {})\n", x, y); }

        // distance to another point
        double distance_to(const Point &other) const {
            const double dx = static_cast<double>(x - other.x);
            const double dy = static_cast<double>(y - other.y);
            return std::sqrt(dx * dx + dy * dy);
        }
    };

    // --- Example usage ---
    Point p1(2, 3);
    p1.print(); // (2, 3)

    p1.move(1, -1);
    p1.print(); // (3, 2)

    Point p2;
    p2.print(); // (0, 0)

    fmt::print("Distance between p1 and p2: {}\n", p1.distance_to(p2));

    return 0; /* exit gracefully*/
}
