#pragma once

#include <set>
#include "io/managers/InputManagerBase.h"

#include "engine/defines.h"
#include "io/collectors/InputCollectorBase.h"

class InputCollectorBase;

class InputManager {
public:
    void update(chrono_time delta);
    void handle_event(const std::string& event_type, const std::map<std::wstring, std::any>& event_data);

    void register_manager(const std::string& event_type, std::shared_ptr<InputManagerBase> manager);
    void remove_manager(const std::string& event_type);
    [[nodiscard]] std::weak_ptr<InputManagerBase> get_manager(const std::string& event_type) const;

    void register_collector(const std::string& collector_name, std::shared_ptr<InputCollectorBase> collector);
    void remove_collector(const std::string& collector_name);
    void enable_collector(const std::string& collector_name);
    void disable_collector(const std::string& collector_name);

private:
    std::map<std::string, std::shared_ptr<InputManagerBase>> managers;
    std::map<std::string, std::shared_ptr<InputCollectorBase>> collectors;
    std::set<std::string> enabled_collectors;
};
