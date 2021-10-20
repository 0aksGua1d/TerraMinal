#include "ConEnterWeakScope.h"

#include <iostream>

#include "con_script/Logical.h"

namespace ConScript {
    void ConOpEnterWeakScope::inner_execute(std::shared_ptr<Stack>& stack, const std::vector<std::any>& arguments,
                                      std::vector<std::any>& returns,
                                      std::vector<std::any>& variables, ConRegs& regs) {
        auto new_logical = std::any_cast<std::weak_ptr<Logical>>(
                this->logical_loc.get_value(regs, variables, arguments, returns, stack));
        stack = std::make_shared<Stack>(std::shared_ptr<Logical>(new_logical)->local_scope, stack);
    }

    ConOpType ConOpEnterWeakScope::get_type() {
        return ConOpType::ConEnterWeakScope;
    }
}
