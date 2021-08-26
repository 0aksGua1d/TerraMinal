#pragma once

#include "con_script/ops/ConOp.h"
#include "con_script/ConLocation.h"

namespace ConScript {
    class ConOpMove : public ConOp {
    public:
        ConOpMove(ConLocation src, ConLocation dest) : src(std::move(src)), dest(std::move(dest)) {}

    protected:
        void inner_execute(std::shared_ptr<Stack>& stack, std::vector<std::any>& arguments, std::vector<std::any>& returns, std::vector<std::any>& variables,
                     ConRegs& regs) override;
        ConOpType get_type() override;

    private:
        ConLocation src;
        ConLocation dest;
    };
}
