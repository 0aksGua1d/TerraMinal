#include "ConExistVar.h"

#include "con_script/data/Stack.h"

namespace ConScript {
    void ConOpExistVar::inner_execute(std::shared_ptr<Stack>& stack,const std::vector<std::any>& arguments, std::vector<std::any>& returns,
                                std::vector<std::any>& variables, ConRegs& regs) {
        regs.condition = stack->has_var(this->name);
    }

    ConOpType ConOpExistVar::get_type() {
        return ConOpType::ConExistVar;
    }
}
