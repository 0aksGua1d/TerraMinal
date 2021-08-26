#pragma once

#include <utility>

#include "con_script/Logical.h"
#include "Renderable.h"
#include "RenderableState.h"

using Logical = ConScript::Logical;

class Component;

class Sprite : public Logical, public Renderable, public std::enable_shared_from_this<Sprite> {
public:
    Sprite(std::vector<std::shared_ptr<RenderableState>> states, size_t starting_state);

    Sprite(const Sprite& other);

    void init_ptr();

    void setCurrentState(size_t index);

    bool need_update(size_t dTimeMilli) const override;

    void update(size_t dTimeMilli) override;

    std::shared_ptr<Renderable> copy() override;

    void draw(std::shared_ptr<Screen> screen, Position pos, unsigned long id) const override;

    void erase(std::shared_ptr<Screen> screen, Position pos, unsigned long id) const override;

private:
    std::vector<std::shared_ptr<RenderableState>> states;
    PROPERTY(int, current_state_index);
    PROPERTY(std::vector<std::any>, states_logicals);
    PROPERTY(std::weak_ptr<Logical>, parent_component);
    std::weak_ptr<Component> component;
};
