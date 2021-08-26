#pragma once

#include "LogFIlter.h"

template<typename filter>
class LambdaLogFilter : public LogFilter {
public:
    template<typename... Args>
    LambdaLogFilter(Args... args);

    bool should_log(const Log& log) override;
private:
    filter _filter;
};