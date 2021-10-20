#include <windows.h>
#include <iostream>
#include <chrono>

#include "io/collectors/windows/WindowsConsoleInputCollector.h"
#include "io/managers/ManagerNames.h"
#include "io/managers/keyboard/KeyboardInputManager.h"
#include "io/managers/focus/FocusInputManager.h"
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
    Logger::info("Starting game", {
        {"Mode set", std::to_string(SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS))}
    });
    auto start = std::chrono::high_resolution_clock::now();
    auto input_manager = std::make_shared<InputManager>();
    auto keyboard_manager = std::make_shared<KeyboardInputManager>();
    input_manager->register_manager(ManagerNames::KEYBOARD_TYPE, keyboard_manager);
    input_manager->register_manager(ManagerNames::FOCUS_TYPE, std::make_shared<FocusInputManager>());
    input_manager->register_collector("a", std::make_shared<WindowsConsoleInputCollector>(input_manager));
    input_manager->enable_collector("a");
    auto engine = std::make_shared<Engine>(input_manager, std::map<std::wstring, std::shared_ptr<InputControllerBase>>{});
    auto loader = std::make_shared<Loader>();
    loader->load_sprites("test_sprite.tms");
    auto scene = std::make_shared<Scene>(loader);
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 13; ++j) {
            auto id = scene->createComponent(Position({i * 8 + 1, 1 + j * 4}), L"Testing");
            auto comp = scene->getComponent(id);
            auto sprite = (Sprite*)(GET_PTR(comp, sprite_logical).get());
            auto states_logicals = GET_PTR(sprite, states_logicals);
            auto current_state_index = GET_PTR(sprite, current_state_index);
            auto first_state = std::any_cast<std::shared_ptr<Logical>>(states_logicals[current_state_index]);
            keyboard_manager->add_listener(L"space", first_state->local_scope->functions->at(L"start"), std::make_shared<ConScript::Stack>(first_state->local_scope));
        }
    }
    engine->world->add_scene(L"main", scene);
    engine->world->set_scene(L"main");
    engine->run();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;
}