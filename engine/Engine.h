#pragma once
#include "World.h"
#include "Screen.h"
#include <thread>
#include <string>

class Engine {
public:
	Engine(std::shared_ptr<InputManager>, std::map<std::wstring, std::shared_ptr<InputControllerBase>>, float fps = 60.0f);
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;
	Engine(Engine&&) = delete;
	Engine& operator=(Engine&&) = delete;

	void load(const std::wstring& filepath) {};

	void run();
private:
	void gameThreadLoop();

public:
	std::shared_ptr<World> world;
	std::shared_ptr<Screen> screen;
	float wanted_fps;
	bool is_running;
};