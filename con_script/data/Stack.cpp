#include <exceptions/con_script/stack_exception.h>
#include "Stack.h"

namespace ConScript {
    bool Stack::has_local_var(const std::wstring& name) {
        return this->local_scope->variables.find(name) != this->local_scope->variables.end();
    }

    bool Stack::has_var(const std::wstring& name) {
        if (has_local_var(name)) {
            return true;
        }
        if (nullptr == this->prev_frame) {
            return false;
        }
        return this->prev_frame->has_var(name);
    }

    std::any& ConScript::Stack::get_var(const std::wstring& name) {
        if (this->has_var(name)) {
            return this->local_scope->variables[name];
        }
        if (nullptr == this->prev_frame) {
            throw VariableNotFound(name);
        }
        return this->prev_frame->get_var(name);
    }

    void Stack::set_var(const std::wstring& name, const std::any& value) {
        if (this->has_var(name)) {
            local_scope->variables[name] = value;
        } else {
            if (nullptr == this->prev_frame) {
                throw VariableNotFound(name);
            }
            this->prev_frame->get_var(name);
        }
    }

    bool Stack::has_local_func(const std::wstring& name) {
        return this->local_scope->functions->count(name) != 0;
    }

    bool Stack::has_func(const std::wstring& name) {
        if (has_local_func(name)) {
            return true;
        }
        if (nullptr == this->prev_frame) {
            return false;
        }
        return this->prev_frame->has_func(name);
    }

    std::shared_ptr<ConFunction> Stack::get_func(const std::wstring& name) {
        if (this->has_local_func(name)) {
            return this->local_scope->functions->at(name);
        }
        if (nullptr == this->prev_frame) {
            throw VariableNotFound(name);
        }
        return this->prev_frame->get_func(name);
    }
}
