#include "ConVectorSet.h"
#include "logger/Logger.h"

namespace ConScript {
    void ConOpVectorSet::inner_execute(std::shared_ptr<Stack>& stack, std::vector<std::any>& arguments, std::vector<std::any>& returns,
                                 std::vector<std::any>& variables, ConRegs& regs) {
        auto index = std::any_cast<int>(this->index_loc.get_value(regs, variables, arguments, returns, stack));
        auto value = this->src_loc.get_value(regs, variables, arguments, returns, stack);
        std::any_cast<std::vector<std::any>>(this->vector_loc.get_value(regs, variables, arguments, returns, stack))[index] = value;
    }

    ConOpType ConOpVectorSet::get_type() {
        return ConOpType::ConVectorSet;
    }
}
