#pragma once

#include <memory>
#include <any>

struct ParsedState {
    std::unique_ptr<std::any> chars = nullptr;
    std::unique_ptr<std::any> attrs = nullptr;
    std::unique_ptr<std::any> frames = nullptr;
    std::unique_ptr<std::any> anims = nullptr;
    std::unique_ptr<std::any> states = nullptr;
};
