#include "KeyboardInputManager.h"

#include "logger/Logger.h"
#include "io/managers/ManagerNames.h"
#include "KeyboardGestures.h"


KeyboardInputManager::KeyboardInputManager() {
    SET_PTR(this, states, {});
}

std::string KeyboardInputManager::get_name() const {
    return ManagerNames::KEYBOARD_TYPE;
}

std::any KeyboardInputManager::get_state(const std::wstring& key) const {
    auto states = GET_PTR(this, states);
    auto key_state = states.find(key);
    if (states.end() != key_state) {
        auto state_num = std::any_cast<int>(key_state->second);
        return KeyState{.is_down=(state_num & 0x1) == 0x1, .is_held=(state_num & 0x2) == 0x2};
    }

    return KeyState{.is_down=false, .is_held=false}; // Default is to assume the button is up
}

void KeyboardInputManager::handle_event(const std::map<std::wstring, std::any>& event_data) {
    try {
        const auto key = std::any_cast<std::wstring>(event_data.at(EVENT_KEY));
        const auto down = std::any_cast<bool>(event_data.at(EVENT_DOWN));
        const auto state = std::any_cast<KeyEventFlags>(event_data.at(EVENT_STATE));
        const bool& held = down && (!std::any_cast<KeyState>(this->get_state(key)).is_down);
        const std::wstring gesture = down
                                    ? (
                                        held
                                        ? KeyboardGestures::HOLD // If previously down and now held
                                        : KeyboardGestures::DOWN // If first time down
                                    )
                                    : KeyboardGestures::UP;

        auto key_listeners = this->callbacks.find(key);
        if (this->callbacks.end() != key_listeners) {
            std::vector<std::any> callback_args{key, down, gesture, state};
            std::vector<std::any> returns{};
            for (auto&[id, listener] : key_listeners->second) {
                try {
                    listener.func->call(callback_args, returns, listener.stack);
                } catch (const std::bad_any_cast&) {
                    Logger::error("Bad func call");
                }
            }
        }
        auto states = GET_PTR(this, states);
        int raw_key_state = down + 2 * held;
        states[key] = std::any((int)raw_key_state);
        SET_PTR(this, states, states);
    } catch (const std::bad_any_cast&) {
        Logger::error("Bad keyboard event");
        return;
    }
}
