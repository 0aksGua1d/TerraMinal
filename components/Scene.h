#pragma once

#include <utility>

#include "engine/defines.h"
#include "engine/Screen.h"
#include "engine/Position.h"
#include "utils/property.h"
#include "Component.h"
#include "loader/SpriteLoader/SpriteLoader.h"
#include "loader/Loader.h"
#include "con_script/Logical.h"

class World;

class Scene : public ConScript::Logical {
public:
    explicit Scene(std::shared_ptr<Loader> loader) : Logical(), loader(std::move(loader)) {}

    size_t createComponent(Position pos, const std::wstring& sprite_name);

    void removeComponent(size_t compnent_id);

    virtual void update(chrono_time new_time);

    virtual void draw(const std::shared_ptr<Screen>& screen);

    std::shared_ptr<Component> getComponent(size_t id);

private:
    std::map<size_t, std::shared_ptr<Component>> components;
    std::shared_ptr<Loader> loader;
    std::weak_ptr<World> world;

PROPERTY(size_t, root);
PROPERTY((std::map<size_t, std::shared_ptr<Logical>>), components);
};
