#include "Animation.h"

#include <utility>

#include "logger/Logger.h"
#include "RenderableState.h"
#include "con_script/data/Stack.h"

using ConOp = ConScript::ConOp;

Animation::Animation(std::shared_ptr<std::vector<std::pair<size_t, std::shared_ptr<Frame>>>> frames,
                     bool is_repeating) : Logical(), frames(std::move(frames)) {
    SET_PTR(this, is_repeating, is_repeating);
    SET_PTR(this, frame_index, 0);
    SET_PTR(this, time_in_frame, 0);
    SET_PTR(this, is_running, true);
}

bool Animation::need_update(size_t dTimeMilli) const {
    return GET_PTR(this, is_running);
}

void Animation::update(size_t dTimeMilli) {
    int time_in_frame = GET_PTR(this, time_in_frame);
    bool is_repeating = GET_PTR(this, is_repeating);
    int index = GET_PTR(this, frame_index);

    time_in_frame += dTimeMilli;
    while (this->frames->at(index).first <= time_in_frame) {
        time_in_frame -= this->frames->at(index).first;
        if (this->frames->size() - 1 == index) {
            if (is_repeating) {
                index = 0;
            } else {
                SET_PTR(this, is_running, false);
                auto shared_state = this->renderable_state.lock();
                if (nullptr != shared_state) {
                    auto stack = std::make_shared<ConScript::Stack>(shared_state->local_scope);
                    if (stack->has_func(EVENT_ANIMATION_END)) {
                        std::vector<std::any> args{};
                        std::vector<std::any> rets{};
                        stack->get_func(EVENT_ANIMATION_END)->call(args, rets, stack);
                    }
                }
                break;
            }
        } else {
            index++;
        }
        auto shared_state = this->renderable_state.lock();
        auto stack = std::make_shared<ConScript::Stack>(shared_state->local_scope);
        if (stack->has_func(EVENT_FRAME_CALLBACK)) {
            std::vector<std::any> args{index};
            std::vector<std::any> rets{};
            stack->get_func(EVENT_FRAME_CALLBACK)->call(args, rets, stack);
        }
    }
    SET_PTR(this, frame_index, index);
    SET_PTR(this, time_in_frame, time_in_frame);
}

std::shared_ptr<Renderable> Animation::copy() {
    return std::make_shared<Animation>(*this);
}

void Animation::draw(std::shared_ptr<Screen> screen, Position pos, unsigned long id) const {
    size_t frame_index = GET_PTR(this, frame_index);
    this->frames->at(frame_index).second->draw(screen, pos, id);
}

void Animation::erase(std::shared_ptr<Screen> screen, Position pos, unsigned long id) const {
    this->frames->at(GET_PTR(this, frame_index)).second->erase(screen, pos, id);
}
