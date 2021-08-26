#include <regex>
#include "renderable/Frame.h"
#include "renderable/Animation.h"
#include "AnimationsLoader1.h"

const std::wregex ID_REGEX(L"^id:(\\d+)$", std::wregex::optimize);
const std::wregex IS_REPEATING_REGEX(L"^is_repeating:(false|true)$", std::wregex::optimize);
const std::wregex FRAME_COUNT_REGEX(L"^frames:(\\d+)$", std::wregex::optimize);
const std::wregex FRAME_REGEX(L"^(\\d+)-(\\d+)$", std::wregex::optimize);


bool AnimationsLoader1::can_parse(const ParsedState& current_parsing_state) {
    return nullptr != current_parsing_state.frames;
}


void AnimationsLoader1::parse(std::wifstream& file_stream, size_t count, ParsedState& parsing_state) {
    std::map<size_t, std::shared_ptr<Animation>> animations;

    auto frames = std::any_cast<std::map<size_t, std::shared_ptr<Frame>>>(*parsing_state.frames);

    for (size_t i = 0; i < count; ++i) {
        auto id_line_res = AnimationsLoader1::parse_line(file_stream, ID_REGEX);
        size_t id = parse_int(id_line_res[0]);

        auto chars_line_res = AnimationsLoader1::parse_line(file_stream, IS_REPEATING_REGEX);
        bool is_repeating = L"true" == chars_line_res[0];

        auto frame_count_line_res = AnimationsLoader1::parse_line(file_stream, FRAME_COUNT_REGEX);
        size_t frame_count = parse_int(frame_count_line_res[0]);

        auto anim_frames = std::make_shared<std::vector<std::pair<size_t, std::shared_ptr<Frame>>>>();
        for (size_t j = 0; j < frame_count;++j) {
            auto frame_line_res = AnimationsLoader1::parse_line(file_stream, FRAME_REGEX);
            size_t frame_id = AnimationsLoader1::parse_int(frame_line_res[0]);
            size_t frame_time = AnimationsLoader1::parse_int(frame_line_res[1]) * 1000;
            anim_frames->push_back({frame_time, frames.at(frame_id)});
        }

        animations[id] = std::make_shared<Animation>(anim_frames, is_repeating);
    }

    parsing_state.anims = std::make_unique<std::any>(animations);
}
