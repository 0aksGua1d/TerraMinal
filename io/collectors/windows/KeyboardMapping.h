#pragma once

#include <map>

namespace KeyboardMapping {
    extern const std::map<int, std::wstring>& get_key_mapping();

    extern const std::map<std::wstring, int>& get_key_inverse_mapping();
}
