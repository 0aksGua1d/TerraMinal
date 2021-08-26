#include "ConExitScope.h"

namespace ConScript {
    void ConOpExitScope::inner_execute(std::shared_ptr<Stack>& stack, std::vector<std::any>& arguments, std::vector<std::any>& returns,
                                  std::vector<std::any>& variables, ConRegs& regs) {
        stack = stack->prev_frame;
    }

    ConOpType ConOpExitScope::get_type() {
        return ConOpType::ConExitScope;
    }
}
