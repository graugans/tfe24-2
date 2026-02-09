#include "json_logger.hpp"
#include <nlohmann/json.hpp>
#include <chrono>
#include <iomanip>
#include <sstream>

using json = nlohmann::json;

JsonLogger::JsonLogger(std::string path)
    : out_(std::move(path), std::ios::app) {
}

JsonLogger::~JsonLogger() = default;

void JsonLogger::log(const std::string& level,
                     const std::string& message,
                     const Context& context) {
    if (!out_) {
        return;
    }

    // Aktuellen Zeitstempel generieren
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time_t), "%Y-%m-%dT%H:%M:%S");
    std::string timestamp = oss.str();

    // JSON-Objekt erstellen
    json log_obj;
    log_obj["timestamp"] = timestamp;
    log_obj["level"] = level;
    log_obj["message"] = message;

    // Kontext hinzufügen
    if (!context.empty()) {
        json context_obj = json::object();
        for (const auto& [key, value] : context) {
            context_obj[key] = value;
        }
        log_obj["context"] = context_obj;
    }

    // Als NDJSON schreiben (eine Zeile pro Log-Eintrag)
    out_ << log_obj.dump() << "\n";
    out_.flush();
}
