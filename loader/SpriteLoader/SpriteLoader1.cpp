#include <regex>

#include "SpriteLoader1.h"

#include "logger/Logger.h"
#include "utils/string_converter.h"
#include "renderable/Frame.h"
#include "ParsedState.h"
#include "SubLoaderBase.h"
#include "CharsLoader/CharsLoader1.h"
#include "AttrsLoader/AttrsLoader1.h"
#include "FramesLoader/FramesLoader1.h"
#include "AnimationsLoader/AnimationsLoader1.h"
#include "StatesLoader/StatesLoader1.h"

const std::wregex NAME_REGEX(L"^name:(.+)$", std::wregex::optimize);
const std::wregex SECTION_REGEX(L"^-----(\\w+):(\\d+)$", std::wregex::optimize);

const std::map<std::wstring, std::shared_ptr<SubLoaderBase>> SUB_PARSERS{
        {L"chars",      std::make_shared<CharsLoader1>()},
        {L"attrs",      std::make_shared<AttrsLoader1>()},
        {L"frames",     std::make_shared<FramesLoader1>()},
        {L"animations", std::make_shared<AnimationsLoader1>()},
        {L"states",     std::make_shared<StatesLoader1>()},
};

size_t SpriteLoader1::get_version() {
    return 1;
}

std::map<std::wstring, std::shared_ptr<Sprite>> SpriteLoader1::load_file(std::wifstream& file_stream) {
    auto name_line_res = SubLoaderBase::parse_line(file_stream, NAME_REGEX);
    std::wstring sprite_name = name_line_res[0];

    ParsedState state;

    std::vector<std::wstring> sub_parser_line_res;
    while (!(sub_parser_line_res = SubLoaderBase::parse_line(file_stream, SECTION_REGEX)).empty()) {
        std::wstring sub_parser_name = sub_parser_line_res[0];
        size_t sub_parser_arg = SubLoaderBase::parse_int(sub_parser_line_res[1]);

        auto sub_parser_ptr = SUB_PARSERS.find(sub_parser_name);
        if (SUB_PARSERS.end() == sub_parser_ptr) {
            Logger::error("Unknown SubParser name", {{"SubParser", string_converter.to_bytes(sub_parser_name)}});
            return {};
        }

        if (!sub_parser_ptr->second->can_parse(state)) {
            Logger::error("SubParser can not parse", {{"SubParser", string_converter.to_bytes(sub_parser_name)}});
            return {};
        }

        sub_parser_ptr->second->parse(file_stream, sub_parser_arg, state);
    }

    if (nullptr == state.states) {
        Logger::error("States Were not generated");
        return {};
    }
    auto[start_state_index, states] = std::any_cast<std::pair<size_t, std::vector<std::shared_ptr<RenderableState>>>>(
            *state.states);
    return {{sprite_name, std::make_shared<Sprite>(states, start_state_index)}};
}
