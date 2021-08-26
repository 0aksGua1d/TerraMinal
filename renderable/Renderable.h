#pragma once
#include <memory>

#include "../engine/Position.h"
#include "../engine/Screen.h"

class Renderable {
public:
	Renderable() = default;
	Renderable(const Renderable&) = default;
	Renderable& operator=(const Renderable&) = default;
	Renderable(Renderable&&) = default;
	Renderable& operator=(Renderable&&) = default;
	~Renderable() = default;


	[[nodiscard]] virtual bool need_update(size_t dTimeMilli) const = 0;
	virtual void update(size_t dTimeMilli) = 0;
	virtual std::shared_ptr<Renderable> copy() = 0;

	virtual void draw(std::shared_ptr<Screen> screen, Position pos, unsigned long id) const = 0;
	virtual void erase(std::shared_ptr<Screen> screen, Position pos, unsigned long id) const = 0;
};