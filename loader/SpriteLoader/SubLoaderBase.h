#pragma once

#include <string>
#include <regex>
#include <vector>
#include <fstream>

#include "ParsedState.h"

class SubLoaderBase {
public:
    virtual bool can_parse(const ParsedState& current_parsing_state) = 0;
    virtual void parse(std::wifstream& file_stream, size_t count, ParsedState& parsing_state) = 0;

    static std::vector<std::wstring> parse_line(std::wifstream& file_stream, const std::wregex& regex);
    static size_t parse_int(std::wstring_view str, size_t default_value = 0);
};
