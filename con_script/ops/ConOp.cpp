#include "ConOp.h"

#include "logger/Logger.h"

void ConScript::ConOp::execute(std::shared_ptr<Stack>& stack, std::vector<std::any>& arguments,
                               std::vector<std::any>& returns, std::vector<std::any>& variables,
                               ConScript::ConRegs& regs) {
    try {
        this->inner_execute(stack, arguments, returns, variables, regs);
    } catch (const std::exception& e) {
        Logger::error("Exception thrown in ConOp", {{"Exception", e.what()}, {"ConOp", ConOpNames[this->get_type()]}});
    }
}
