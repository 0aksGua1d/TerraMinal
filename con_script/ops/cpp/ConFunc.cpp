#include "ConFunc.h"
#include "utils/call.h"

namespace ConScript {
    template<typename Func>
    void ConOpFunc<Func>::inner_execute(std::shared_ptr<Stack>& stack, std::vector<std::any>& arguments,
                                  std::vector<std::any>& returns, std::vector<std::any>& variables, ConRegs& regs) {
        std::vector<std::any> args;
        args.emplace_back(stack);
        for (auto arg_loc : this->arg_locs) {
            args.push_back(arg_loc.get_value(regs, variables, arguments, returns, stack));
        }
        auto ret = utils::call(this->func, args);
        this->ret_loc.set_value(regs, variables, arguments, returns, stack, ret);
    }

    template<typename Func>
    ConOpType ConOpFunc<Func>::get_type() {
        return ConOpType::ConFunc;
    }
}
