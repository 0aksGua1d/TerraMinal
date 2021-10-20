#include "WindowsConsoleInputCollector.h"

#include <sstream>

#include "logger/Logger.h"
#include "io/managers/focus/FocusInputManager.h"
#include "io/managers/keyboard/KeyboardInputManager.h"
#include "io/managers/ManagerNames.h"
#include "KeyboardMapping.h"


WindowsConsoleInputCollector::WindowsConsoleInputCollector(std::weak_ptr<InputManager> input_manager)
        : InputCollectorBase(std::move(input_manager)) {
    this->stdin_handle = GetStdHandle(STD_INPUT_HANDLE);
}

void handle_focus_event(const std::shared_ptr<InputManager>& manager, const FOCUS_EVENT_RECORD& record) {
    manager->handle_event(ManagerNames::FOCUS_TYPE, {
            {EVENT_FOCUS, record.bSetFocus},
    });
}

void handle_keyboard_event(const std::shared_ptr<InputManager>& manager, const KEY_EVENT_RECORD& record) {
    const auto& mapping = KeyboardMapping::get_key_mapping();

    const auto& key = mapping.find(record.wVirtualKeyCode);
    if (mapping.end() == key) { return; }

    bool is_down = record.bKeyDown;

    manager->handle_event(ManagerNames::KEYBOARD_TYPE, {
        {EVENT_KEY,   key->second},
        {EVENT_DOWN,  is_down},
        {EVENT_STATE, KeyEventFlags{
            .capslock = 0 != (record.dwControlKeyState & CAPSLOCK_ON),
            .left_alt = 0 != (record.dwControlKeyState & LEFT_ALT_PRESSED),
            .right_alt = 0 != (record.dwControlKeyState & RIGHT_ALT_PRESSED),
            .left_control = 0 != (record.dwControlKeyState & LEFT_CTRL_PRESSED),
            .right_control = 0 != (record.dwControlKeyState & RIGHT_CTRL_PRESSED),
            .shift = 0 != (record.dwControlKeyState & SHIFT_PRESSED),
            .numlock = 0 != (record.dwControlKeyState & NUMLOCK_ON),
            .scroll_lock = 0 != (record.dwControlKeyState & SCROLLLOCK_ON),
        }},
    });
}

void handle_menu_event(const std::shared_ptr<InputManager>& manager, const MENU_EVENT_RECORD& record) {

}

void handle_mouse_event(const std::shared_ptr<InputManager>& manager, const MOUSE_EVENT_RECORD& record) {

}

void handle_buffer_size_event(const std::shared_ptr<InputManager>& manager, const WINDOW_BUFFER_SIZE_RECORD& record) {

}

void handle_event(const std::shared_ptr<InputManager>& manager, const INPUT_RECORD& record) {
    switch (record.EventType) {
        case FOCUS_EVENT:
            handle_focus_event(manager, record.Event.FocusEvent);
            break;
        case KEY_EVENT:
            handle_keyboard_event(manager, record.Event.KeyEvent);
            break;
        case MENU_EVENT:
            handle_menu_event(manager, record.Event.MenuEvent);
            break;
        case MOUSE_EVENT:
            handle_mouse_event(manager, record.Event.MouseEvent);
            break;
        case WINDOW_BUFFER_SIZE_EVENT:
            handle_buffer_size_event(manager, record.Event.WindowBufferSizeEvent);
            break;

        default:
            std::stringstream ss;
            ss << "Unknown event type: ";
            ss << record.EventType;
            Logger::warn(ss.str());
            break;
    }
}

void WindowsConsoleInputCollector::update(chrono_time delta) {
    DWORD event_count = 0;
    auto logger_context = Logger::create_context("Windows input collector");
    if (!GetNumberOfConsoleInputEvents(stdin_handle, &event_count)) {
        Logger::error("Failed to get number of events");
        return;
    }

    std::vector<INPUT_RECORD> records;
    records.resize(event_count);

    DWORD records_read = 0;
    if (!ReadConsoleInput(stdin_handle, records.data(), event_count, &records_read)) {
        Logger::error("Failed to read event records");
        return;
    }

    auto input_manager = this->input_manager.lock();
    if (nullptr == input_manager) {
        Logger::error("input manager expired");
        return;
    }

    for (DWORD i = 0; i < records_read; ++i) {
        handle_event(input_manager, records.at(i));
    }
}

void WindowsConsoleInputCollector::install() noexcept {}

void WindowsConsoleInputCollector::uninstall() noexcept {}
