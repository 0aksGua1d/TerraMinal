#include "WindowsMouseInputController.h"

#include <windows.h>

#include "logger/Logger.h"

void WindowsMouseInputController::enable() noexcept {
    auto logger_context = Logger::create_context("WindowsKeyboardInputController_enable");

    HANDLE input_handle = GetStdHandle(STD_INPUT_HANDLE);
    DWORD console_mode;

    if (!GetConsoleMode(input_handle, &console_mode)) {
        Logger::error("Failed to get console input mode");
        return;
    }

    console_mode |= ENABLE_MOUSE_INPUT;

    if (!SetConsoleMode(input_handle, console_mode)) {
        Logger::error("Failed to set console input mode");
        return;

    }
}

void WindowsMouseInputController::disable() noexcept {
    auto logger_context = Logger::create_context("WindowsKeyboardInputController_disable");

    HANDLE input_handle = GetStdHandle(STD_INPUT_HANDLE);
    DWORD console_mode;

    if (!GetConsoleMode(input_handle, &console_mode)) {
        Logger::error("Failed to get console input mode");
        return;
    }

    console_mode &= ~ENABLE_MOUSE_INPUT;

    if (!SetConsoleMode(input_handle, console_mode)) {
        Logger::error("Failed to set console input mode");
        return;

    }
}
