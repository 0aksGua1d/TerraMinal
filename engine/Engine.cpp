#include "Engine.h"
#include "defines.h"

Engine::Engine(std::shared_ptr<InputManager> input_manager,
               std::map<std::wstring, std::shared_ptr<InputControllerBase>> input_controllers,
               float wanted_fps) : wanted_fps(wanted_fps),
                                   screen(std::make_shared<Screen>()),
                                   world(std::make_shared<World>(std::move(input_manager), std::move(input_controllers))),
                                   is_running(false) {
}

void Engine::gameThreadLoop() {
    this->screen->set_fullscreen();
    this->is_running = true;
    auto start_time = std::chrono::high_resolution_clock::now();
    auto last_frame = std::chrono::high_resolution_clock::now();
    while (this->is_running) {
        auto current_time = std::chrono::high_resolution_clock::now();
        this->world->update(current_time);
        this->world->draw(this->screen);
        this->screen->draw();

        auto frame_diff = current_time - last_frame;
        if (std::chrono::duration_cast<std::chrono::nanoseconds>(frame_diff).count() < 16000000 &&
            std::chrono::duration_cast<std::chrono::seconds>(frame_diff).count() == 0) {
            std::this_thread::sleep_for(std::chrono::nanoseconds(1600000) - frame_diff);
        }
        last_frame = current_time;

        auto diff = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count();
        if (5 <= diff) {
            this->is_running = false;
        }
    }
};

void Engine::run() {
    std::thread engine_thread = std::thread(&Engine::gameThreadLoop, this);
    engine_thread.join();
}
