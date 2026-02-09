#pragma once
#include "ilogger.hpp"

/**
 * @brief Console Logger - gibt Logs mit fmt formatiert auf STDOUT aus
 */
class FmtConsoleLogger : public ILogger {
public:
    /**
     * @brief Protokolliert eine Nachricht auf der Konsole
     */
    void log(const std::string& level,
             const std::string& message,
             const Context& context = {}) override;
};
