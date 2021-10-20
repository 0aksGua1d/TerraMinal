#pragma once
#include <map>
#include <memory>

#include "engine/defines.h"
#include "con_script/ConFunction.h"
#include "con_script/Logical.h"
#include "renderable/Sprite.h"
#include "engine/Screen.h"

static size_t next_id = 0;

using Logical = ConScript::Logical;
using ConFunction = ConScript::ConFunction;

class Component : public Logical, public std::enable_shared_from_this<Component>
{
public:
	Component(Position pos, const std::shared_ptr<Sprite>& sprite);
	Component(const Component& other);
	Component& operator=(const Component& other) = delete;
	Component(Component&&) = default;
	Component& operator=(Component&&) = default;

	void init_ptr();

	void addChild(const std::wstring& name, const std::shared_ptr<Component>& new_child);
	void removeChild(const std::wstring& name);
	void addCallback(const std::wstring& event_name, std::shared_ptr<ConFunction> callback);
	void removeCallback(const std::wstring& event_name);

	void changePos(Position& new_pos);
	void draw(const std::shared_ptr<Screen>& screen);
	void update(chrono_time current);

	size_t get_id() { return this->id; }

protected:
	bool hasPosChanged() const;

private:
	size_t id;
	Position old_pos;
	std::shared_ptr<Sprite> sprite;

    PROPERTY(Position , pos);
    PROPERTY(std::shared_ptr<Logical>, sprite_logical);
    PROPERTY((std::map<std::wstring, unsigned long>), tree);
    PROPERTY(chrono_time, last_time);
    PROPERTY(chrono_time, current);

    std::weak_ptr<Component> parent;
};
