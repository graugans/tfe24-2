#pragma once
#include "ilogger.hpp"
#include <fstream>
#include <string>

/**
 * @brief JSON Logger - schreibt Logs als NDJSON in eine Datei
 */
class JsonLogger : public ILogger {
private:
    std::ofstream out_;

public:
    /**
     * @brief Konstruktor
     * @param path Pfad zur Log-Datei
     */
    explicit JsonLogger(std::string path);

    /**
     * @brief Destruktor
     */
    ~JsonLogger() override;

    /**
     * @brief Protokolliert eine Nachricht als JSON-Objekt
     */
    void log(const std::string& level,
             const std::string& message,
             const Context& context = {}) override;
};
