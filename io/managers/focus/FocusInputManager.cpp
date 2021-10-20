#include "FocusInputManager.h"

#include "logger/Logger.h"
#include "io/managers/ManagerNames.h"

FocusInputManager::FocusInputManager() {
    SET_PTR(this, in_focus, true);
}

void FocusInputManager::handle_event(const std::map<std::wstring, std::any>& event_data) {
    auto data_ptr = event_data.find(EVENT_FOCUS);
    if (event_data.end() != data_ptr) {
        try {
            bool in_focus = std::any_cast<bool>(data_ptr->second);
            SET_PTR(this, in_focus, in_focus);

            const std::vector<std::any> callback_args{in_focus};
            std::vector<std::any> returns{};
            auto _callbacks = this->callbacks.find(IN_FOCUS);
            if (this->callbacks.end() != _callbacks) {
                for (auto&[id, listener] : _callbacks->second) {
                    listener.func->call(callback_args, returns, listener.stack);
                }
            }
        } catch (const std::bad_any_cast&) {
            Logger::error("Bad focus event");
        }
    }
}

std::any FocusInputManager::get_state(const std::wstring& key) const {
    if (IN_FOCUS == key) {
        return GET_PTR(this, in_focus);
    }
    throw ConScript::NoSuchVariable(key);
}

std::string FocusInputManager::get_name() const {
    return ManagerNames::FOCUS_TYPE;
}
