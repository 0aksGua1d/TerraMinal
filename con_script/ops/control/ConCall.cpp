#include "logger/Logger.h"
#include "utils/string_converter.h"
#include "ConCall.h"

namespace ConScript {
    void ConOpCall::inner_execute(std::shared_ptr<Stack>& stack, const std::vector<std::any>& parent_func_args,
                            std::vector<std::any>& parent_func_returns,
                            std::vector<std::any>& variables, ConRegs& regs) {
        std::vector<std::any> func_args;
        std::vector<std::any> func_returns;
        auto func_name = std::any_cast<std::wstring>(
                this->func_name_loc.get_value(regs, variables, parent_func_args, parent_func_returns,
                                              stack));
        if (!stack->has_func(func_name)) {
            Logger::warn("No such function", {
                {"FuncName", string_converter.to_bytes(func_name)},
            });
            return;
        }

        func_returns.resize(this->returns.size());
        for (auto& arg_loc : this->args) {
            func_args.push_back(arg_loc.get_value(
                    regs, variables, parent_func_args, parent_func_returns, stack));
        }

        stack->get_func(func_name)->call(func_args, func_returns, stack);

        for (size_t i = 0; i < this->returns.size(); ++i) {
            this->returns[i].set_value(regs, variables, parent_func_args, parent_func_returns, stack, func_returns[i]);
        }
    }

    ConOpType ConOpCall::get_type() {
        return ConOpType::ConCall;
    }
}
