#include "FramesLoader1.h"

#include <regex>

#include "renderable/Frame.h"

const std::wregex ID_REGEX(L"^id:(\\d+)$", std::wregex::optimize);
const std::wregex CHARS_REGEX(L"^chars:(\\d+)$", std::wregex::optimize);
const std::wregex ATTRS_REGEX(L"^attrs:(\\d+)$", std::wregex::optimize);
const std::wregex POS_REGEX(L"^pos:(\\d+)-(\\d+)$", std::wregex::optimize);


bool FramesLoader1::can_parse(const ParsedState& current_parsing_state) {
    if (nullptr == current_parsing_state.chars) {
        return false;
    }
    if (nullptr == current_parsing_state.attrs) {
        return false;
    }
    return true;
}


void FramesLoader1::parse(std::wifstream& file_stream, size_t count, ParsedState& parsing_state) {
    std::map<size_t, std::shared_ptr<Frame>> frames;

    auto chars = std::any_cast<std::map<size_t, std::shared_ptr<CharBuffer>>>(*parsing_state.chars);
    auto attrs = std::any_cast<std::map<size_t, std::shared_ptr<AttrBuffer>>>(*parsing_state.attrs);

    for (size_t i = 0; i < count; ++i) {
        auto id_line_res = FramesLoader1::parse_line(file_stream, ID_REGEX);
        size_t id = parse_int(id_line_res[0]);

        auto chars_line_res = FramesLoader1::parse_line(file_stream, CHARS_REGEX);
        size_t chars_id = parse_int(chars_line_res[0]);

        auto attrs_line_res = FramesLoader1::parse_line(file_stream, ATTRS_REGEX);
        size_t attrs_id = parse_int(attrs_line_res[0]);

        auto pos_line_res = FramesLoader1::parse_line(file_stream, POS_REGEX);
        COORD offset{
                (short)(-parse_int(pos_line_res[0])),
                (short)(-parse_int(pos_line_res[1]))
        };

        frames[id] = std::make_shared<Frame>(chars.at(chars_id), attrs.at(attrs_id), offset, offset);
    }

    parsing_state.frames = std::make_unique<std::any>(frames);
}
