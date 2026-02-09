#pragma once
#include <string>
#include <map>

using Context = std::map<std::string, std::string>;

/**
 * @brief Interface für Logger-Strategien
 */
struct ILogger {
    virtual ~ILogger() = default;

    /**
     * @brief Protokolliert eine Nachricht mit Kontext
     * @param level Loglevel (info, warn, error)
     * @param message Die zu protokollierende Nachricht
     * @param context Kontext als Key-Value-Paare
     */
    virtual void log(const std::string& level,
                     const std::string& message,
                     const Context& context = {}) = 0;
};
