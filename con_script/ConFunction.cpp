#include <logger/Logger.h>
#include "ConFunction.h"

IdGenerator ConScript::ConFunction::generator;

ConScript::ConFunction::ConFunction(std::shared_ptr<std::vector<std::shared_ptr<ConOp>>> ops,
                                    std::vector<std::any> init_static_data, size_t extra_vars,
                                    size_t arguments_count, size_t return_count)
        : ops(std::move(ops)), static_data(std::move(init_static_data)), extra_vars(extra_vars),
        arguments_count(arguments_count), return_count(return_count) {}

void ConScript::ConFunction::call(std::vector<std::any>& arguments,
                                  std::vector<std::any>& returns, std::shared_ptr<Stack> stack) {
    std::vector<std::any> variables(this->static_data.begin(), this->static_data.end());
    for (size_t i = 0; i < this->extra_vars; ++i) {
        variables.emplace_back(0);
    }
    auto logger_context = Logger::create_context(std::to_string(generator.generate_id()));
    ConRegs regs{};
    for (const auto& op : *this->ops) {
        if (regs._break) {
            break;
        }
        op->execute(stack, arguments, returns, variables, regs);
    }
}
