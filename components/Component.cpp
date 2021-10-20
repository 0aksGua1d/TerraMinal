#include "Component.h"

#include <utility>
#include <iostream>

Component::Component(Position pos, const std::shared_ptr<Sprite>& sprite) : Logical(), old_pos(pos), id(next_id++),
                                                                            sprite(std::dynamic_pointer_cast<Sprite>(
                                                                                    sprite->copy())) {
    SET_PTR(this, pos, pos);
    SET_PTR(this, tree, {});
    SET_PTR(this, sprite_logical, this->sprite);
    SET_PTR(this, current, std::chrono::system_clock::from_time_t(0));
    SET_PTR(this, last_time, std::chrono::system_clock::from_time_t(0));
    old_pos.z += 1;
}

Component::Component(const Component& other) : Logical(other), old_pos(other.old_pos), parent(other.parent),
                                               sprite(std::dynamic_pointer_cast<Sprite>(other.sprite->copy())),
                                               id(next_id++) {
    SET_PTR(this, sprite_logical, std::dynamic_pointer_cast<Logical>(this->sprite));
    this->init_ptr();
}

void Component::addChild(const std::wstring& name, const std::shared_ptr<Component>& new_child) {
    new_child->parent = weak_from_this();
    auto tree = GET_PTR(this, tree);
    tree[name] = new_child->id;
    SET_PTR(this, tree, tree);
}

void Component::removeChild(const std::wstring& name) {
    auto tree = GET_PTR(this, tree);
    if (tree.find(name) != tree.end()) {
        tree.erase(name);
    }
    SET_PTR(this, tree, tree);
}

void Component::addCallback(const std::wstring& event_name, std::shared_ptr<ConFunction> callback) {
    this->local_scope->functions->emplace(event_name, std::move(callback));
}

void Component::removeCallback(const std::wstring& event_name) {
    if (this->local_scope->functions->count(event_name) != 0) {
        this->local_scope->functions->erase(event_name);
    }
}

void Component::draw(const std::shared_ptr<Screen>& screen) {
    if (nullptr != this->sprite) {
        auto current = GET_PTR(this, current);
        auto last_time = GET_PTR(this, last_time);
        auto overall_change = std::chrono::duration_cast<std::chrono::microseconds>(current - last_time);
        bool needs_update = this->sprite->need_update(overall_change.count());
        bool pos_changed = this->hasPosChanged();
        if (needs_update || pos_changed) {
            this->sprite->erase(screen, this->old_pos, this->id);
            if (needs_update) {
                this->sprite->update(overall_change.count());
                last_time += overall_change;
                SET_PTR(this, last_time, last_time);
            }
            this->sprite->draw(screen, GET_PTR(this, pos), this->id);

            this->old_pos = GET_PTR(this, pos);
        }
    }
}

void Component::update(chrono_time new_time) {
    SET_PTR(this, current, new_time);
    if (std::chrono::system_clock::from_time_t(0) == GET_PTR(this, last_time)) {
        SET_PTR(this, last_time, new_time);
    }
}

bool Component::hasPosChanged() const {
    Position pos = GET_PTR(this, pos);
    return pos.x != old_pos.x || pos.y != old_pos.y || pos.z != old_pos.z;
}

void Component::changePos(Position& new_pos) {
    SET_PTR(this, pos, new_pos);
}

void Component::init_ptr() {
    this->sprite->component = weak_from_this();
    SET_PTR(this->sprite, parent_component, weak_from_this());
    this->sprite->init_ptr();
}
