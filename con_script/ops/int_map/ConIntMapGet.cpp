#include <iostream>
#include "ConIntMapGet.h"

namespace ConScript {
    void ConOpIntMapGet::inner_execute(std::shared_ptr<Stack>& stack, const std::vector<std::any>& arguments, std::vector<std::any>& returns,
                                 std::vector<std::any>& variables, ConRegs& regs) {
        auto index = std::any_cast<int>(this->index_loc.get_value(regs, variables, arguments, returns, stack));

        auto map = std::any_cast<std::map<size_t, std::any>>(this->map_loc.get_value(regs, variables, arguments, returns, stack));
        auto value_ptr = map.find(index);
        if (map.end() == value_ptr) {
            regs.condition = false;
        } else {
            regs.condition = true;
            auto value = std::any_cast<std::wstring>(*value_ptr);
            this->dest_loc.set_value(regs, variables, arguments, returns, stack, value);
        }
    }

    ConOpType ConOpIntMapGet::get_type() {
        return ConOpType::ConIntMapGet;
    }
}
