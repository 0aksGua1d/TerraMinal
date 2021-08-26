#include "ConMove.h"
#include "logger/Logger.h"

namespace ConScript {
    void ConOpMove::inner_execute(std::shared_ptr<Stack>& stack, std::vector<std::any>& arguments, std::vector<std::any>& returns,
                                       std::vector<std::any>& variables, ConRegs& regs) {
        auto value = this->src.get_value(regs, variables, arguments, returns, stack);
        this->dest.set_value(regs, variables, arguments, returns, stack, value);
    }

    ConOpType ConOpMove::get_type() {
        return ConOpType::ConMove;
    }
}
