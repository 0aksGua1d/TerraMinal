#pragma once

#include "data/Scope.h"

namespace ConScript {
    class Logical {
    public:
        Logical() : local_scope(std::make_shared<Scope>()) {}
        explicit Logical(const std::shared_ptr<Scope>& scope) : local_scope(std::make_shared<Scope>(*scope)) {}

        Logical(const Logical& other) : local_scope(std::make_shared<Scope>(*other.local_scope)) {}

        Logical(Logical&& other)  noexcept : local_scope(other.local_scope) {}

        Logical& operator=(const Logical& other) {
            this->local_scope = std::make_shared<Scope>(*other.local_scope);
            return *this;
        }

        Logical& operator=(Logical&& other) {
            this->local_scope = std::move(other.local_scope);
            return *this;
        }

    public:
        std::shared_ptr<Scope> local_scope;
    };
}
