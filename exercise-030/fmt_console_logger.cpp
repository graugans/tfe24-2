#include "fmt_console_logger.hpp"
#include <fmt/format.h>
#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream>


void FmtConsoleLogger::log(const std::string& level,
                           const std::string& message,
                           const Context& context) {
    // Kontext-String bauen
    std::string context_str;
    if (!context.empty()) {
        std::vector<std::string> pairs;
        for (const auto& [key, value] : context) {
            pairs.push_back(fmt::format("{}={}", key, value));
        }
        context_str = fmt::format(" [{}]", fmt::join(pairs, ", "));
    }

    // Log mit Farben/Formatierung ausgeben (vereinacht ohne echte Farbcodes)
    fmt::print("[{}] {}{}\n", level, message, context_str);
}
