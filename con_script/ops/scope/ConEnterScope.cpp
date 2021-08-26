#include "ConEnterScope.h"

#include "con_script/Logical.h"

namespace ConScript {
    void ConOpEnterScope::inner_execute(std::shared_ptr<Stack>& stack, std::vector<std::any>& arguments, std::vector<std::any>& returns,
                                  std::vector<std::any>& variables, ConRegs& regs) {
        auto new_logical = std::any_cast<std::shared_ptr<Logical>>(this->logical_loc.get_value(regs, variables, arguments, returns, stack));
        stack = std::make_shared<Stack>(new_logical->local_scope, stack);
    }

    ConOpType ConOpEnterScope::get_type() {
        return ConOpType::ConEnterScope;
    }
}
