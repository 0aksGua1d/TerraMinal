#pragma once

#include "con_script/ops/ConOp.h"
#include "con_script/ConLocation.h"

namespace ConScript {
    class ConOpEnterScope : public ConOp {
    public:
        explicit ConOpEnterScope(ConLocation logical_loc) : logical_loc(std::move(logical_loc)) {}
    protected:
        void inner_execute(std::shared_ptr<Stack>& stack, const std::vector<std::any>& arguments, std::vector<std::any>& returns, std::vector<std::any>& variables,
                     ConRegs& regs) override;
        ConOpType get_type() override;

    private:
        ConLocation logical_loc;
    };
}
