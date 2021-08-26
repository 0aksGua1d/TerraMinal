#include "ConCondition.h"

namespace ConScript {
    void ConOpCondition::inner_execute(std::shared_ptr<Stack>& stack, std::vector<std::any>& arguments, std::vector<std::any>& returns,
                                 std::vector<std::any>& variables, ConRegs& regs) {
        auto ops = regs.condition ? this->if_ops : this->else_ops;
        if (nullptr != ops) {
            for (auto op_ptr = ops->begin(); op_ptr != ops->end() || regs._break; op_ptr++) {
                auto op = *op_ptr;
                op->execute(stack, arguments, returns, variables, regs);
            }
        }
    }

    ConOpType ConOpCondition::get_type() {
        return ConOpType::ConCondition;
    }
}
