#pragma once

#include <utility>
#include <memory>
#include <any>

#include "Scope.h"

namespace ConScript {
    class ConFunction;

    class Stack {
    public:
        explicit Stack(std::shared_ptr<Stack> prev_stack = nullptr) : prev_frame(std::move(prev_stack)), local_scope(std::make_shared<Scope>()) {}
        explicit Stack(std::shared_ptr<Scope> local_scope, std::shared_ptr<Stack> prev_stack = nullptr) : prev_frame(std::move(prev_stack)), local_scope(std::move(local_scope)) {}

    private:
        bool has_local_func(const std::wstring&);
        bool has_local_var(const std::wstring&);

    public:
        std::shared_ptr<Scope> local_scope;
        std::shared_ptr<Stack> prev_frame;

        bool has_func(const std::wstring&);
        std::shared_ptr<ConFunction> get_func(const std::wstring&);

        bool has_var(const std::wstring&);
        std::any& get_var(const std::wstring&);
        void set_var(const std::wstring&, const std::any&);
    };
}