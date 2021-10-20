#pragma once

#include <utility>

#include "con_script/ops/ConOp.h"
#include "con_script/ConLocation.h"

namespace ConScript {
    class ConOpAdd : public ConOp {
    public:
        ConOpAdd(ConLocation src1, ConLocation src2, ConLocation dest) : src1(std::move(src1)), src2(std::move(src2)),
                                                                         dest(std::move(dest)) {}

    protected:
        void
        inner_execute(std::shared_ptr<Stack>& stack, const std::vector<std::any>& arguments, std::vector<std::any>& returns,
                      std::vector<std::any>& variables,
                      ConRegs& regs) override;

        ConOpType get_type() override;

    private:
        ConLocation src1;
        ConLocation src2;
        ConLocation dest;
    };
}
