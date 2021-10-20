#pragma once

#include "io/InputManager.h"

class InputManager;

class InputControllerBase {
public:
    virtual void enable() noexcept = 0;
    virtual void disable() noexcept = 0;
};
