#pragma once

#include "io/managers/InputManagerBase.h"
#include "KeyState.h"
#include "utils/property.h"

// Event data keys
static const std::wstring EVENT_KEY(L"key");
static const std::wstring EVENT_STATE(L"state");
static const std::wstring EVENT_DOWN(L"down");


class KeyboardInputManager : public InputManagerBase {
public:
    KeyboardInputManager();

    void handle_event(const std::map<std::wstring, std::any>& event_data) override;

    [[nodiscard]] std::any get_state(const std::wstring& key) const override;
    [[nodiscard]] std::string get_name() const override;

private:
    PROPERTY((std::map<std::wstring, std::any>), states);
};
