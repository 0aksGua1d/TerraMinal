#include "Sprite.h"

static const std::wstring CURRENT_STATE = L"current_state";
static const std::wstring STATES = L"states";

Sprite::Sprite(std::vector<std::shared_ptr<RenderableState>> states, size_t starting_state) : states(std::move(states)) {
    SET_PTR(this, current_state_index, starting_state);
    std::vector<std::any> states_logicals;
    for (auto& state : this->states) {
        states_logicals.emplace_back(std::dynamic_pointer_cast<Logical>(state));
    }
    SET_PTR(this, states_logicals, states_logicals);
}

Sprite::Sprite(const Sprite& other) : Logical(other) {
    this->states.clear();
    std::vector<std::any> states_logicals;
    for (auto& state : other.states) {
        state->sprite = weak_from_this();
        SET_PTR(state, parent_sprite, weak_from_this());
        auto new_ptr = std::make_shared<RenderableState>(*state);
        this->states.push_back(new_ptr);
        states_logicals.emplace_back(std::dynamic_pointer_cast<Logical>(new_ptr));
    }
    SET_PTR(this, states_logicals, states_logicals);
}

void Sprite::init_ptr() {
    for (auto& state : this->states) {
        state->sprite = weak_from_this();
        SET_PTR(state, parent_sprite, weak_from_this());
        state->init_ptr();
    }
}

std::shared_ptr<Renderable> Sprite::copy()
{
	return std::make_shared<Sprite>(*this);
}

void Sprite::draw(std::shared_ptr<Screen> screen, Position pos, unsigned long id) const
{
    int index = GET_PTR(this, current_state_index);
    this->states[index]->draw(screen, pos, id);
}

void Sprite::erase(std::shared_ptr<Screen> screen, Position pos, unsigned long id) const
{
	this->states[GET_PTR(this, current_state_index)]->erase(screen, pos, id);
}

void Sprite::setCurrentState(size_t index)
{
    SET_PTR(this, current_state_index, index);
}

bool Sprite::need_update(size_t dTimeMilli) const
{
    auto current = GET_PTR(this, current_state_index);
    bool res = this->states[current]->need_update(dTimeMilli);
    return res;
}

void Sprite::update(size_t dTimeMilli)
{
    auto current = GET_PTR(this, current_state_index);
    this->states[current]->update(dTimeMilli);
	// TODO: make the state change the state and reset it
}
