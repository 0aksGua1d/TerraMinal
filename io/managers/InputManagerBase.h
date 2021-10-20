#pragma once

#include <string>
#include <any>

#include "engine/defines.h"

#include "con_script/ConFunction.h"
#include "con_script/data/Stack.h"
#include "con_script/Logical.h"

typedef struct {
    std::shared_ptr<ConScript::ConFunction> func;
    std::shared_ptr<ConScript::Stack> stack;
} callback;

class InputManagerBase : public ConScript::Logical {
public:
    virtual void update(chrono_time delta);
    virtual void handle_event(const std::map<std::wstring, std::any>& event_data) = 0;

    [[nodiscard]] virtual std::any get_state(const std::wstring& key) const = 0;
    [[nodiscard]] virtual std::string get_name() const = 0;

    virtual int add_listener(const std::wstring& key, std::shared_ptr<ConScript::ConFunction> func, std::shared_ptr<ConScript::Stack> stack);
    virtual void remove_listener(int id);

protected:
    std::map<std::wstring, std::map<int, callback>> callbacks;
    std::map<int, std::wstring> callback_keys;
private:
    int last_id = 0;
};
