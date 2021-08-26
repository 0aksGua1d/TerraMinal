#pragma once

#include "con_script/ops/ConOp.h"

namespace ConScript {
    class ConOpExistVar : public ConOp {
    public:
        explicit ConOpExistVar(std::wstring name) : name(std::move(name)) {}

    protected:
        void inner_execute(std::shared_ptr<Stack>& stack, std::vector<std::any>& arguments, std::vector<std::any>& returns, std::vector<std::any>& variables,
                     ConRegs& regs) override;
        ConOpType get_type() override;

    private:
        std::wstring name;
    };
}
