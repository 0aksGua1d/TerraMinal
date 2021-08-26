#include <logger/Logger.h>
#include <utils/string_converter.h>
#include "SubLoaderBase.h"

std::vector<std::wstring> SubLoaderBase::parse_line(std::wifstream& file_stream, const std::wregex& regex) {
    std::wstring line;
    if (!std::getline(file_stream, line)) {
        if (!file_stream.eof()) {
            Logger::error("File ended when expected more lines");
        }
        return {};
    }
    std::wsmatch match;
    if (!std::regex_match(line, match, regex)) {
        Logger::error("Failed to parse line", {
            {"line", string_converter.to_bytes(line)},
            {"line_size", std::to_string(string_converter.to_bytes(line).size())},
            {"offset in file", std::to_string(file_stream.tellg())},
            });
        return {};
    }
    std::vector<std::wstring> results;
    for (size_t i = 0; i < match.size() - 1;++i) {
        results.push_back(match[i + 1]);
    }
    return results;
}

size_t SubLoaderBase::parse_int(const std::wstring_view str, size_t default_value)  {
    size_t i = default_value;
    std::wstringstream wstringstream;
    wstringstream << str;
    wstringstream >> i;
    return i;
}
