#include <windows.h>
#include <iostream>
#include <vector>
#include <chrono>
#include "con_script/ops/control/ConMove.h"
#include "renderable/Frame.h"
#include "renderable/Animation.h"
#include "renderable/Sprite.h"
#include "engine/Engine.h"
#include "logger/Logger.h"
#include "logger/log_writer/FileLogWriter.h"
#include "logger/log_formatter/LineLogFormatter.h"
#include "logger/log_filter/TrueLogFilter.h"

#define DEFAULT_TEXT_ATTR 0xf
#define SINGLE_CELL_ATTR (COMMON_LVB_GRID_HORIZONTAL | COMMON_LVB_GRID_LVERTICAL | COMMON_LVB_GRID_RVERTICAL | COMMON_LVB_UNDERSCORE)
#define CELL_START_ATTR (COMMON_LVB_GRID_HORIZONTAL | COMMON_LVB_GRID_LVERTICAL | COMMON_LVB_UNDERSCORE)
#define CELL_MID_ATTR (COMMON_LVB_GRID_HORIZONTAL | COMMON_LVB_UNDERSCORE)
#define CELL_END_ATTR (COMMON_LVB_GRID_HORIZONTAL | COMMON_LVB_GRID_RVERTICAL | COMMON_LVB_GRID_RVERTICAL | COMMON_LVB_UNDERSCORE)


int main() {
    Logger::add_writing_operation(std::make_shared<FileLogWriter>("logs.txt"),
                                  std::make_shared<LineLogFormatter>(),
                                  std::make_shared<TrueLogFilter>());
    Logger::info("Starting game");
    auto start = std::chrono::high_resolution_clock::now();
    auto engine = std::make_shared<Engine>();
    auto loader = std::make_shared<Loader>();
    loader->load_sprites("test_sprite.tms");
    auto scene = std::make_shared<Scene>(loader);
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 13; ++j) {
            auto id = scene->createComponent(Position({i * 8 + 1, 1 + j * 4}), L"Testing");
            auto comp = scene->getComponent(id);
            auto sprite = GET_PTR(comp, sprite_logical);
            auto states_logicals = std::any_cast<std::vector<std::any>>(
                    sprite->local_scope->variables.at(L"states_logicals"));
            auto first_state = std::any_cast<std::shared_ptr<Logical>>(states_logicals[0]);
            auto animation = std::any_cast<std::shared_ptr<Logical>>(
                    first_state->local_scope->variables.at(L"animation_logical"));
            int k = 900000 - ((i * 3 + j) * 10000);
            animation->local_scope->variables[L"time_in_frame"] = k;
        }
    }
    engine->world->add_scene(L"main", scene);
    engine->world->set_scene(L"main");
    engine->run();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;
}