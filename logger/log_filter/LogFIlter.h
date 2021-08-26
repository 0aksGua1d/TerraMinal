#pragma once

#include "../Log.h"

class LogFilter {
public:
    virtual bool should_log(const Log& log) = 0;
};
