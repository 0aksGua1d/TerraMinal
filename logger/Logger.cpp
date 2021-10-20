#include <chrono>
#include <sstream>

#include "utils/context.h"
#include "Logger.h"

std::unique_ptr<Logger> Logger::logger_singleton;
std::vector<std::tuple<std::shared_ptr<LogWriter>, std::shared_ptr<LogFormatter>, std::shared_ptr<LogFilter>>> Logger::writing_operations;
std::vector<std::string> Logger::context_list;

void Logger::log(Log& log) {
    if (nullptr == Logger::logger_singleton) {
        Logger::logger_singleton = std::make_unique<Logger>();
    }
    {
        std::stringstream ss;
        bool should_add_separator = false;
        for (const auto& context : Logger::context_list) {
            if (should_add_separator) {
                ss << "-";
            }
            ss << context;
            should_add_separator = true;
        }
        log.extra["context"] = ss.str();
    }
    for (auto&[writer, formatter, filter] : Logger::writing_operations) {
        if (filter->should_log(log)) {
            writer->write(formatter->format(log));
        }
    }
}

void Logger::log(LOG_LVL level, const std::string& message, const std::map<std::string, std::string>& extra) {
    Log log = {.message=message, .level=level, .log_time=std::time(nullptr), .extra=extra};
    Logger::log(log);
}

void Logger::debug(const std::string& message, const std::map<std::string, std::string>& extra) {
    Logger::log(Log::DEBUG, message, extra);
}

void Logger::info(const std::string& message, const std::map<std::string, std::string>& extra) {
    Logger::log(LOG_LVL::LVL_INFO, message, extra);
}

void Logger::warn(const std::string& message, const std::map<std::string, std::string>& extra) {
    Logger::log(LOG_LVL::LVL_WARNING, message, extra);
}

void Logger::error(const std::string& message, const std::map<std::string, std::string>& extra) {
    Logger::log(LOG_LVL::LVL_ERROR, message, extra);
}

void Logger::critical(const std::string& message, const std::map<std::string, std::string>& extra) {
    Logger::log(LOG_LVL::LVL_CRITICAL, message, extra);
}

void Logger::add_writing_operation(const std::shared_ptr<LogWriter>& writer,
                                   const std::shared_ptr<LogFormatter>& formatter,
                                   const std::shared_ptr<LogFilter>& filter) {
    Logger::writing_operations.emplace_back(writer, formatter, filter);
}

void Logger::pop_context() {
    Logger::context_list.erase(Logger::context_list.end() - 1, Logger::context_list.end());
}

Context<void(*)()> Logger::create_context(const std::string& context_name) {
    Logger::context_list.push_back(context_name);
    const auto pop_context = Logger::pop_context;
    return Context(pop_context);
}
