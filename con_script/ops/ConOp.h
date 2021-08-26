#pragma once

#include <any>
#include <memory>
#include <vector>

#include "con_script/ConRegs.h"
#include "con_script/ops/ConOpType.h"

namespace ConScript {
    class Stack;
    class ConOp {
    public:
        virtual void
        execute(std::shared_ptr<Stack>& stack, std::vector<std::any>& arguments, std::vector<std::any>& returns, std::vector<std::any>& variables,
                ConRegs& regs);

    protected:
        virtual void
        inner_execute(std::shared_ptr<Stack>& stack, std::vector<std::any>& arguments, std::vector<std::any>& returns, std::vector<std::any>& variables,
                ConRegs& regs) = 0;
        virtual ConOpType get_type() = 0;
    };
}

