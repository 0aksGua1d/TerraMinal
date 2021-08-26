#pragma once

#include "../SubLoaderBase.h"

class AttrsLoader1 : public SubLoaderBase {
public:
    bool can_parse(const ParsedState& current_parsing_state) override;
    void parse(std::wifstream& file_stream, size_t count, ParsedState& parsing_state) override;
};
