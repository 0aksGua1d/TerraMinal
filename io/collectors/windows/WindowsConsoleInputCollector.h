#pragma once

#include "io/collectors/InputCollectorBase.h"

#include "windows.h"

class WindowsConsoleInputCollector : public InputCollectorBase {
public:
    explicit WindowsConsoleInputCollector(std::weak_ptr<InputManager> input_manager);
    void install() noexcept override;
    void uninstall() noexcept override;
    void update(chrono_time delta) override;

private:
    HANDLE stdin_handle;
};
