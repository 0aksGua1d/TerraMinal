#include "CharsLoader1.h"

#include <regex>

#include "logger/Logger.h"
#include "renderable/Frame.h"
#include "utils/unicode.h"

const std::wregex ID_REGEX(L"^id:(\\d+)$", std::wregex::optimize);
const std::wregex SIZE_REGEX(L"^size:(\\d+)-(\\d+)$", std::wregex::optimize);

bool CharsLoader1::can_parse(const ParsedState& current_parsing_state) {
    return true;
}


void CharsLoader1::parse(std::wifstream& file_stream, size_t count, ParsedState& parsing_state) {
    std::map<size_t, std::shared_ptr<CharBuffer>> char_buffers;
    for (size_t i = 0; i < count; ++i) {
        size_t id;
        size_t max_line_length;
        size_t line_count;

        auto id_line_res = CharsLoader1::parse_line(file_stream, ID_REGEX);
        id = CharsLoader1::parse_int(id_line_res[0]);

        auto size_line_res = CharsLoader1::parse_line(file_stream, SIZE_REGEX);
        max_line_length = CharsLoader1::parse_int(size_line_res[0]);
        line_count = CharsLoader1::parse_int(size_line_res[1]);

        auto chars = std::make_shared<CharBuffer>();

        for(size_t j = 0;j < line_count;j++) {
            std::wstring chars_line;
            if (!std::getline(file_stream, chars_line)) {
                Logger::error("Failed to parse chars segment", {
                    {"ExpectedLineCount", std::to_string(line_count)},
                    {"LineCount", std::to_string(j)},
                });
                return;
            }
            chars_line = convert_from_utf8(chars_line);
            if (chars_line.size() < max_line_length) {
                Logger::error("Failed to parse chars line", {
                    {"ExpectedLineLength", std::to_string(max_line_length)},
                    {"LineLength", std::to_string(chars_line.size())},
                    });
                return;
            } else if (chars_line.size() > max_line_length) {
                Logger::warn("Line is too long, cutting it down", {
                    {"ExpectedLineLength", std::to_string(max_line_length)},
                    {"LineLength", std::to_string(chars_line.size())},
                    });
            }
            chars->push_back(chars_line.substr(0, max_line_length));
        }
        char_buffers[id] = chars;
    }

    parsing_state.chars = std::make_unique<std::any>(char_buffers);
}
