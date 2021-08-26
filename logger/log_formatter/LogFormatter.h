#pragma once

#include "../Log.h"

class LogFormatter {
public:
    virtual std::string format(const Log& log) = 0;
};
