#pragma once

class LogWriter {
public:
    virtual void write(const std::string& buffer) = 0;
};
