#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"

#include "logger.hpp"
#include "json_logger.hpp"
#include "fmt_console_logger.hpp"

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

    /* Strategy Pattern Demonstration - Logger mit austauschbaren Strategien */
    fmt::print("\n=== Logger Strategy Pattern Demo ===\n\n");

    // Strategie 1: JSON Logger - protokolliert in Datei
    fmt::print("[1] Nutze JSON Logger (Datei)\n");
    auto json_logger = std::make_unique<JsonLogger>("app.log.jsonl");
    Logger logger(std::move(json_logger));

    Context auth_context = {{"user", "alice"}, {"module", "auth"}};
    Context security_context = {{"severity", "high"}, {"ip", "192.168.1.100"}};

    logger.info("System gestartet", {{"version", "1.0"}});
    logger.info("Benutzer angemeldet", auth_context);
    logger.warn("Verdächtige Aktivität erkannt", security_context);
    logger.error("Authentifizierung fehlgeschlagen", auth_context);

    fmt::print("  => Logs geschrieben zu 'app.log.jsonl'\n\n");

    // Zur Laufzeit zu anderer Strategie wechseln
    fmt::print("[2] Wechsel zu FmtConsoleLogger (Konsole)\n");
    logger.set_strategy(std::make_unique<FmtConsoleLogger>());

    logger.info("Gewechselt zu Console Logging", {{"logger", "FmtConsoleLogger"}});
    logger.warn("Dies wird auf der Konsole ausgegeben", {{"level", "notice"}});
    logger.error("Fehler-Beispiel mit Kontext", {{"code", "ERR_001"}, {"action", "retry"}});

    fmt::print("\n  => Logs direkt auf der Konsole ausgegeben\n");

    fmt::print("\n=== Demo abgeschlossen ===\n");
    fmt::print("Hinweis: Datei 'app.log.jsonl' mit JSON-Logs wurde erstellt.\n");

    return 0; /* exit gracefully*/
}
