#include <regex>

#include "AttrsLoader1.h"

#include "logger/Logger.h"
#include "utils/string_converter.h"
#include "renderable/Frame.h"

const std::wregex ID_REGEX(L"^id:(\\d+)$", std::wregex::optimize);
const std::wregex SIZE_REGEX(L"^size:(\\d+)-(\\d+)$", std::wregex::optimize);

const std::map<wchar_t, WORD> ATTR_MAP = {
        {L'.', 0x0}, // dark black
        {L'b', 0x1}, // dark blue
        {L'g', 0x2}, // dark green
        {L'c', 0x3}, // dark cyan
        {L'r', 0x4}, // dark red
        {L'p', 0x5}, // dark purple
        {L'y', 0x6}, // dark yellow
        {L'w', 0x7}, // bright grey
        {L'X', 0x8}, // dark grey
        {L'B', 0x9}, // bright blue
        {L'G', 0xa}, // bright green
        {L'C', 0xb}, // bright cyan
        {L'R', 0xc}, // bright red
        {L'P', 0xd}, // bright purple
        {L'Y', 0xe}, // bright yellow
        {L'W', 0xf}, // bright white
};

bool AttrsLoader1::can_parse(const ParsedState& current_parsing_state) {
    return true;
}

std::vector<WORD> parse_attrs_string(const std::wstring& raw_attrs) {
    std::vector<WORD> attrs;
    for (size_t i = 0; i < raw_attrs.size() / 2;++i) {
        auto foreground_attr = ATTR_MAP.find(raw_attrs[i]);
        auto background_attr = ATTR_MAP.find(raw_attrs[i + raw_attrs.size() / 2]);
        WORD attr = 0;
        if (ATTR_MAP.end() != foreground_attr) {
            attr |= foreground_attr->second;
        } else {
            wchar_t buf[2] = {};
            buf[0] = raw_attrs[i];
            Logger::warn("Unknown attr char", {{"char", string_converter.to_bytes(buf)}});
        }
        if (ATTR_MAP.end() != background_attr) {
            attr |= background_attr->second << 4;
        } else {
            wchar_t buf[2] = {};
            buf[0] = raw_attrs[i + raw_attrs.size() / 2];
            Logger::warn("Unknown attr char", {{"char", string_converter.to_bytes(buf)}});
        }
        attrs.push_back(attr);
    }
    return attrs;
}

void AttrsLoader1::parse(std::wifstream& file_stream, size_t count, ParsedState& parsing_state) {
    std::map<size_t, std::shared_ptr<AttrBuffer>> attr_buffers;
    for (size_t i = 0; i < count; ++i) {
        size_t id;
        size_t max_line_length;
        size_t line_count;

        auto id_line_res = AttrsLoader1::parse_line(file_stream, ID_REGEX);
        id = AttrsLoader1::parse_int(id_line_res[0]);

        auto size_line_res = AttrsLoader1::parse_line(file_stream, SIZE_REGEX);
        max_line_length = AttrsLoader1::parse_int(size_line_res[0]);
        line_count = AttrsLoader1::parse_int(size_line_res[1]);

        auto attrs = std::make_shared<AttrBuffer>();

        for(size_t j = 0;j < line_count;j++) {
            std::wstring attrs_line;
            if (!std::getline(file_stream, attrs_line)) {
                Logger::error("Failed to read attr line");
                return;
            }
            if (attrs_line.size() < max_line_length * 2) {
                Logger::error("Attr line too short", {{"attr_line", string_converter.to_bytes(attrs_line)},
                                                      {"expected_len", std::to_string(max_line_length * 2)}});
                return;
            } else if (attrs_line.size() > max_line_length * 2){
                Logger::warn("Attr line too long", {{"attr_line", string_converter.to_bytes(attrs_line)},
                                                      {"expected_len", std::to_string(max_line_length * 2)}});
            }
            auto short_line = attrs_line.substr(0, max_line_length * 2);
            auto parsed_line = parse_attrs_string(short_line);
            attrs->push_back(parsed_line);
        }
        attr_buffers[id] = attrs;
    }

    parsing_state.attrs = std::make_unique<std::any>(attr_buffers);
}
