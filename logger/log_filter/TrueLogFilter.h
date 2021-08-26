#pragma once

#include "LogFIlter.h"

class TrueLogFilter : public LogFilter {
public:
    bool should_log(const Log& log) override;
};