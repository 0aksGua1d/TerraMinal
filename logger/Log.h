#pragma once

#include <string>
#include <map>

#undef ERROR

enum class LOG_LVL {
    LVL_DEBUG,
    LVL_INFO,
    LVL_WARNING,
    LVL_ERROR,
    LVL_CRITICAL,
};

struct Log {
    std::string message;
    LOG_LVL level;
    time_t log_time;
    std::map<std::string, std::string> extra;
    static constexpr LOG_LVL DEBUG = LOG_LVL::LVL_DEBUG;
    static constexpr LOG_LVL INFO = LOG_LVL::LVL_INFO;
    static constexpr LOG_LVL WARNING = LOG_LVL::LVL_WARNING;
    static constexpr LOG_LVL ERROR = LOG_LVL::LVL_ERROR;
    static constexpr LOG_LVL CRITICAL = LOG_LVL::LVL_CRITICAL;
};
