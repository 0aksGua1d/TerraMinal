#include <sstream>
#include <ctime>
#include <locale>
#include <codecvt>

#include "LineLogFormatter.h"

constexpr auto convert_level(LOG_LVL level) {
    switch (level) {
        case Log::DEBUG:
            return "DEBUG";
        case Log::INFO:
            return "INFO";
        case Log::WARNING:
            return "WARNING";
        case Log::ERROR:
            return "ERROR";
        case Log::CRITICAL:
            return "CRITICAL";
        default:
            return "UNKNOWN";
    }
}

std::string LineLogFormatter::format(const Log& log) {
    std::stringstream stream;
    std::string time_string(std::ctime(&log.log_time));
    time_string = time_string.substr(0, time_string.size() - 1); // removing the newline at the end of ctime
    stream << "[" << convert_level(log.level) << "] " << log.message << " (" << time_string << ")" << std::endl;
    for (const auto&[key, value] : log.extra) {
        stream << "\t" << key << ": " << value << std::endl;
    }
    stream << std::endl;
    return stream.str();
}
