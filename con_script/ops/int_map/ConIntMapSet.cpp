#include "ConIntMapSet.h"

namespace ConScript {
    void ConOpIntMapSet::inner_execute(std::shared_ptr<Stack>& stack, std::vector<std::any>& arguments, std::vector<std::any>& returns,
                                 std::vector<std::any>& variables, ConRegs& regs) {
        try {
            auto index = std::any_cast<int>(this->index_loc.get_value(regs, variables, arguments, returns, stack));
            auto value = this->src_loc.get_value(regs, variables, arguments, returns, stack);
            std::any_cast<std::map<size_t, std::any>>(this->map_loc.get_value(regs, variables, arguments, returns, stack))[index] = value;
            regs.condition = true;
        } catch (const std::exception&) {
            regs.condition = false;
            throw;
        }
    }

    ConOpType ConOpIntMapSet::get_type() {
        return ConOpType::ConIntMapSet;
    }
}
