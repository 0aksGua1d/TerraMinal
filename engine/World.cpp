#include "World.h"

#include <utility>

World::World(std::shared_ptr<InputManager> input_manager,
             std::map<std::wstring, std::shared_ptr<InputControllerBase>> input_controllers) :
        input_manager(std::move(input_manager)),
        input_controllers(std::move(input_controllers)) {}

void World::update(chrono_time new_time) {
    this->input_manager->update(new_time);
    if (nullptr != this->current_scene) {
        this->current_scene->update(new_time);
    }
}

void World::draw(const std::shared_ptr<Screen>& screen) {
    if (nullptr != this->current_scene) {
        this->current_scene->draw(screen);
    }
}

void World::add_scene(const std::wstring& name, std::shared_ptr<Scene> new_scene) {
    this->scenes[name] = std::move(new_scene);
}

bool World::remove_scene(const std::wstring& name) {
    auto res = this->scenes.find(name);
    if (this->scenes.end() == res) {
        return false;
    }
    if (res->second == current_scene) {
        return false;
    }
    this->scenes.erase(res->first);
    return true;
}

bool World::set_scene(const std::wstring& name) {
    auto res = this->scenes.find(name);
    if (this->scenes.end() == res) {
        return false;
    }
    this->current_scene = res->second;
    return true;
}
