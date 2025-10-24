#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"
#include "point.hpp"

auto main(int argc, char **argv) -> int
{
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

    fmt::print("Hello, {}!\n", app.get_name());

    /* INSERT YOUR CODE HERE */
    int x = 0;
    int y = 0;
    int dx = 0;
    int dy = 0;

    app.add_option("--x", x, "Startkoordinate x")->default_val(0);
    app.add_option("--y", y, "Startkoordinate y")->default_val(0);
    app.add_option("--dx", dx, "Verschiebung in x-Richtung")->default_val(0);
    app.add_option("--dy", dy, "Verschiebung in y-Richtung")->default_val(0);

    // Nach dem Parsen nochmal ausführen, da Optionen erst jetzt gesetzt sind
    app.parse(argc, argv);

    Point p(x, y);
    fmt::print("Startpunkt: ");
    p.print();

    p.move(dx, dy);
    fmt::print("Nach move({:+d}, {:+d}): ", dx, dy);
    p.print();
    /* END INSERT */

    return 0; /* exit gracefully*/
}
