#pragma once

#include <string>
#include <map>
#include <memory>
#include <vector>
#include <functional>
#include <codecvt>
#include <locale>
#include <stack>

#include "utils/context.h"
#include "log_filter/LogFIlter.h"
#include "log_formatter/LogFormatter.h"
#include "log_writer/LogWriter.h"
#include "Log.h"

class Logger {
public:
    static void debug(const std::string& message, const std::map<std::string, std::string>& extra = {});
    static void info(const std::string& message, const std::map<std::string, std::string>& extra = {});
    static void warn(const std::string& message, const std::map<std::string, std::string>& extra = {});
    static void error(const std::string& message, const std::map<std::string, std::string>& extra = {});
    static void critical(const std::string& message, const std::map<std::string, std::string>& extra = {});

    static void log(LOG_LVL level, const std::string& message, const std::map<std::string, std::string>& extra = {});

    static void add_writing_operation(const std::shared_ptr<LogWriter>&, const std::shared_ptr<LogFormatter>&, const std::shared_ptr<LogFilter>&);

    static Context<void(*)()> create_context(const std::string& context_name);

private:
    static void pop_context();
    static void log(Log& log);

    static std::unique_ptr<Logger> logger_singleton;
    static std::vector<std::tuple<std::shared_ptr<LogWriter>, std::shared_ptr<LogFormatter>, std::shared_ptr<LogFilter>>> writing_operations;
    static std::vector<std::string> context_list;
};
