#include "ConVectorGet.h"

namespace ConScript {
    void ConOpVectorGet::inner_execute(std::shared_ptr<Stack>& stack, std::vector<std::any>& arguments, std::vector<std::any>& returns,
                                 std::vector<std::any>& variables, ConRegs& regs) {
        auto index = std::any_cast<int>(this->index_loc.get_value(regs, variables, arguments, returns, stack));
        auto value = std::any_cast<std::vector<std::any>>(this->vector_loc.get_value(regs, variables, arguments, returns, stack))[index];
        this->dest_loc.set_value(regs, variables, arguments, returns, stack, value);
    }

    ConOpType ConOpVectorGet::get_type() {
        return ConOpType::ConVectorGet;
    }
}
