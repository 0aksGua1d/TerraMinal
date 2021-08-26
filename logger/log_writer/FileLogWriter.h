#pragma once

#include <fstream>
#include <string>
#include <memory>
#include "LogWriter.h"

class FileLogWriter : public LogWriter {
public:
    explicit FileLogWriter(const std::string& filename);

    void write(const std::string& buffer) override;
private:
    std::ofstream writing_stream;
};
