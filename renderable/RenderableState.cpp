#include "RenderableState.h"

#include <utility>

#include "Animation.h"

RenderableState::RenderableState(const std::shared_ptr<Animation>& animation) : ConScript::Logical(), animation(
        std::dynamic_pointer_cast<Animation>(animation->copy())) {
    SET_PTR(this, animation_logical, std::dynamic_pointer_cast<Logical>(this->animation));
}

RenderableState::RenderableState(const std::shared_ptr<Animation>& animation, const std::shared_ptr<Scope>& init_scope)
        : Logical(init_scope), animation(std::dynamic_pointer_cast<Animation>(animation->copy())) {
    SET_PTR(this, animation_logical, std::dynamic_pointer_cast<Logical>(this->animation));
}


RenderableState::RenderableState(const RenderableState& other) : Logical(other), animation(
        std::make_shared<Animation>(*other.animation)) {
    SET_PTR(this, animation_logical, std::dynamic_pointer_cast<Logical>(this->animation));
}

RenderableState::RenderableState(RenderableState&& other) noexcept : Logical(other), animation(other.animation) {}

RenderableState& RenderableState::operator=(const RenderableState& other) {
    this->animation = std::make_shared<Animation>(*other.animation);
    SET_PTR(this, animation_logical, std::dynamic_pointer_cast<Logical>(this->animation));
    return *this;
}

RenderableState& RenderableState::operator=(RenderableState&& other) noexcept {
    this->animation = other.animation;
    this->local_scope = std::move(other.local_scope);
    return *this;
}

bool RenderableState::need_update(size_t dTimeMilli) const {
    return this->animation->need_update(dTimeMilli);
}

void RenderableState::update(size_t dTimeMilli) {
    this->animation->update(dTimeMilli);
}

std::shared_ptr<Renderable> RenderableState::copy() {
    return std::make_shared<RenderableState>(*this);
}

void RenderableState::draw(std::shared_ptr<Screen> screen, Position pos, unsigned long id) const {
    this->animation->draw(screen, pos, id);
}

void RenderableState::erase(std::shared_ptr<Screen> screen, Position pos, unsigned long id) const {
    this->animation->erase(screen, pos, id);
}

void RenderableState::init_ptr() {
    this->animation->renderable_state = weak_from_this();
    SET_PTR(animation, parent_state, weak_from_this());
}
