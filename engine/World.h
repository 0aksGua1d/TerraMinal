#pragma once
#include <map>
#include <vector>

#include "components/Scene.h"
#include "components/Component.h"
#include "defines.h"

enum class WORLD_FLAGS {
	MOUSE_INPUT = 1,
	AUDIO = 2,
};

class World {
public:
	World() = default;
	World(const World&) = delete;
	World& operator=(const World&) = delete;
	World(World&&) = default;
	World& operator=(World&&) = default;
	~World() = default;

	void add_scene(const std::wstring& name, std::shared_ptr<Scene> scene);
	bool remove_scene(const std::wstring& name);

	bool set_scene(const std::wstring& name);

	virtual void update(chrono_time new_time);

	virtual void draw(const std::shared_ptr<Screen>& screen);

private:
    std::shared_ptr<Scene> current_scene;
    std::map<std::wstring, std::shared_ptr<Scene>> scenes;
};
