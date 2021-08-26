#pragma once

#include <utility>
#include <vector>

#include "con_script/data/Scope.h"
#include "con_script/ConFunction.h"

#include "utils/property.h"
#include "Frame.h"
#include "GraphicBuffers.h"
#include "Renderable.h"
#include "con_script/Logical.h"

const std::wstring EVENT_ANIMATION_END(L"_animation_end");
const std::wstring EVENT_FRAME_CALLBACK(L"_frame_callback");

using Logical = ConScript::Logical;
using Scope = ConScript::Scope;
using ConFunction = ConScript::ConFunction;

class RenderableState;

class Animation : public Logical, public Renderable {
public:
    Animation(std::shared_ptr<std::vector<std::pair<size_t, std::shared_ptr<Frame>>>> frames, bool is_repeating);

	[[nodiscard]] bool need_update(size_t dTimeMilli) const override;
	void update(size_t dTimeMilli) override;
	std::shared_ptr<Renderable> copy() override;
	void draw(std::shared_ptr<Screen> screen, Position pos, unsigned long id) const override;
	void erase(std::shared_ptr<Screen> screen, Position pos, unsigned long id) const override;

//	void reset() { index = 0; time_in_frame = 0; };

private:
    PROPERTY(bool, is_repeating);
    PROPERTY(int, frame_index);
    PROPERTY(int, time_in_frame);
    PROPERTY(bool, is_running);
    PROPERTY((std::map<std::any, std::any>), frame_callbacks);
    PROPERTY(std::weak_ptr<Logical>, parent_state);

    std::shared_ptr<std::vector<std::pair<size_t, std::shared_ptr<Frame>>>> frames;
    std::weak_ptr<RenderableState> renderable_state;
};