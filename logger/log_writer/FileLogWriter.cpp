
#include "FileLogWriter.h"

FileLogWriter::FileLogWriter(const std::string& filename) : writing_stream(filename) {
}

void FileLogWriter::write(const std::string& buffer) {
    this->writing_stream << buffer;
    this->writing_stream.flush();
}