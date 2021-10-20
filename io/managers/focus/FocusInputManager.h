#pragma once

#include "utils/property.h"
#include "io/managers/InputManagerBase.h"

// Event data keys
static const std::wstring EVENT_FOCUS(L"focus");

// states
static const std::wstring IN_FOCUS(L"in_focus");

class FocusInputManager : public InputManagerBase {
public:
    FocusInputManager();

    void handle_event(const std::map<std::wstring, std::any>& event_data) override;

    [[nodiscard]] std::any get_state(const std::wstring& key) const override;
    [[nodiscard]] std::string get_name() const override;

private:
    PROPERTY(bool, in_focus);
};
