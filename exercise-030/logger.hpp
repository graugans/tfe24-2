#pragma once
#include "ilogger.hpp"
#include <memory>
#include <utility>

/**
 * @brief Logger Context - Adapter für Logger-Strategien
 * 
 * Diese Klasse implementiert den Logger als Kontext und nutzt
 * eine ILogger-Strategie zur Ausgabe. Die Strategie kann zur
 * Laufzeit ausgetauscht werden ohne den Kontext zu ändern.
 */
class Logger {
public:
    /**
     * @brief Konstruktor mit Strategie
     * @param strat Initiale Logging-Strategie (unique_ptr übernimmt Ownership)
     */
    explicit Logger(std::unique_ptr<ILogger> strat) 
        : strategy_(std::move(strat)) {}

    /**
     * @brief Wechselt die Logging-Strategie zur Laufzeit
     * @param strat Neue Logging-Strategie
     */
    void set_strategy(std::unique_ptr<ILogger> strat) {
        strategy_ = std::move(strat);
    }

    /**
     * @brief Info-Level Logging
     * @param msg Die zu protokollierende Nachricht
     * @param ctx Optionaler Kontext (Key-Value-Paare)
     */
    void info(const std::string& msg, const Context& ctx = {}) {
        if (strategy_) strategy_->log("info", msg, ctx);
    }

    /**
     * @brief Warning-Level Logging
     * @param msg Die zu protokollierende Nachricht
     * @param ctx Optionaler Kontext (Key-Value-Paare)
     */
    void warn(const std::string& msg, const Context& ctx = {}) {
        if (strategy_) strategy_->log("warn", msg, ctx);
    }

    /**
     * @brief Error-Level Logging
     * @param msg Die zu protokollierende Nachricht
     * @param ctx Optionaler Kontext (Key-Value-Paare)
     */
    void error(const std::string& msg, const Context& ctx = {}) {
        if (strategy_) strategy_->log("error", msg, ctx);
    }

private:
    std::unique_ptr<ILogger> strategy_;  ///< Die aktuelle Logging-Strategie
};
