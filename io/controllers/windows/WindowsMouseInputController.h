#pragma once

#include "io/controllers/InputControllerBase.h"

class WindowsMouseInputController : public InputControllerBase {
public:
    void enable() noexcept override;
    void disable() noexcept override;
};
