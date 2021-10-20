#pragma once

#include "io/InputManager.h"

class InputManager;

class InputCollectorBase {
public:
    explicit InputCollectorBase(std::weak_ptr<InputManager> input_manager);
    virtual void install() noexcept = 0;
    virtual void uninstall() noexcept = 0;
    virtual void update(chrono_time delta) = 0;

protected:
    std::weak_ptr<InputManager> input_manager;
};
