//
// Created by ido on 23/06/2021.
//

#include "Scene.h"

std::shared_ptr<Component> Scene::getComponent(size_t id) {
    if (this->components.end() != this->components.find(id)) {
        return this->components[id];
    }
    return nullptr;
}

size_t Scene::createComponent(Position pos, const std::wstring& sprite_name) {
    auto new_comp = std::make_shared<Component>(pos, this->loader->get_sprite(sprite_name));
    new_comp->init_ptr();
    this->components[new_comp->get_id()] = new_comp;
    return new_comp->get_id();;
}


void Scene::removeComponent(size_t compnent_id) {
    components.erase(compnent_id);
}

void Scene::update(chrono_time new_time) {
    for (auto&[_, component] : this->components) {
        component->update(new_time);
    }
}

void Scene::draw(const std::shared_ptr<Screen>& screen) {
    for (auto&[_, component] : this->components) {
        component->draw(screen);
    }
}

