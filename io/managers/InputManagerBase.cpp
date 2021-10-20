#include "InputManagerBase.h"

void InputManagerBase::update(chrono_time delta) {}

int InputManagerBase::add_listener(const std::wstring& key, std::shared_ptr<ConScript::ConFunction> func,
                                   std::shared_ptr<ConScript::Stack> stack) {
    while(this->callback_keys.end() != this->callback_keys.find(++last_id)) {/* searching next id */}

    this->callbacks[key][last_id] = {std::move(func), std::move(stack)};
    this->callback_keys[last_id] = key;

    return last_id;
}

void InputManagerBase::remove_listener(int id) {
    auto callback_key = this->callback_keys.find(last_id);
    if (this->callback_keys.end() != callback_key) {
        this->callback_keys.erase(id);
        auto key_callback = this->callbacks.find(callback_key->second);
        if (this->callbacks.end() != key_callback) {
            if (key_callback->second.end() != key_callback->second.find(id)) {
                key_callback->second.erase(id);
            }
        }
    }
}
