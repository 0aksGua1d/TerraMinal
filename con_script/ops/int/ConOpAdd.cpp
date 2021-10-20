#include "ConOpAdd.h"

namespace ConScript {
    void ConOpAdd::inner_execute(std::shared_ptr<Stack>& stack, const std::vector<std::any>& arguments, std::vector<std::any>& returns,
                                       std::vector<std::any>& variables, ConRegs& regs) {
        int src1_val = std::any_cast<int>(this->src1.get_value(regs, variables, arguments, returns, stack));
        int src2_val = std::any_cast<int>(this->src2.get_value(regs, variables, arguments, returns, stack));
        int result = src1_val + src2_val;
        this->dest.set_value(regs, variables, arguments, returns, stack, result);
    }

    ConOpType ConOpAdd::get_type() {
        return ConOpType::ConOpAdd;
    }
}
