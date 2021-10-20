#include "InputManager.h"

#include "logger/Logger.h"

void InputManager::handle_event(const std::string& event_type, const std::map<std::wstring, std::any>& event_data) {
    auto manager = this->managers.find(event_type);
    if(this->managers.end() != manager) {
        manager->second->handle_event(event_data);
    } else {
        Logger::warn("UnknownEvent", {
            {"Type", event_type}
        });
    }
}

void InputManager::update(chrono_time delta) {
    std::vector<std::string> bad_collector_names;
    for (auto& collector_name : this->enabled_collectors) {
        auto collector = this->collectors.find(collector_name);
        if (this->collectors.end() != collector) {
            collector->second->update(delta);
        } else {
            bad_collector_names.push_back(collector_name);
        }
    }
    for(const auto& bad_collector_name : bad_collector_names) {
        this->enabled_collectors.erase(bad_collector_name);
    }

    for (auto& manager : this->managers) {
        manager.second->update(delta);
    }
}

void InputManager::register_manager(const std::string& event_type, std::shared_ptr<InputManagerBase> manager) {
    this->managers[event_type] = std::move(manager);
}

void InputManager::remove_manager(const std::string& event_type) {
    this->managers.erase(event_type);
}

std::weak_ptr<InputManagerBase> InputManager::get_manager(const std::string& event_type) const {
    auto manager = this->managers.find(event_type);
    if (this->managers.end() != manager) {
        return manager->second;
    }
    return std::shared_ptr<InputManagerBase>(nullptr);
}

void InputManager::register_collector(const std::string& collector_name, std::shared_ptr<InputCollectorBase> collector) {
    this->collectors[collector_name] = std::move(collector);
}

void InputManager::remove_collector(const std::string& collector_name) {
    this->disable_collector(collector_name);
    if (this->collectors.end() != this->collectors.find(collector_name)) {
        this->collectors.erase(collector_name);
    }
}

void InputManager::enable_collector(const std::string& collector_name) {
    if (this->enabled_collectors.end() == this->enabled_collectors.find(collector_name)) {
        auto collector = this->collectors.find(collector_name);
        if (this->collectors.end() != collector) {
            collector->second->install();
        }
        this->enabled_collectors.insert(collector_name);
    }
}

void InputManager::disable_collector(const std::string& collector_name) {
    if (this->enabled_collectors.end() != this->enabled_collectors.find(collector_name)) {
        this->enabled_collectors.erase(collector_name);
        auto collector = this->collectors.find(collector_name);
        if (this->collectors.end() != collector) {
            collector->second->uninstall();
        }
    }
}
