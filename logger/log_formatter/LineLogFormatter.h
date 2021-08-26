#pragma once

#include "LogFormatter.h"

class LineLogFormatter : public LogFormatter {
public:
    std::string format(const Log& log) override;
};
