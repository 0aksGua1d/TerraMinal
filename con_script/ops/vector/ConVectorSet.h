#pragma once

#include "con_script/ops/ConOp.h"
#include "con_script/ConLocation.h"

namespace ConScript {
    class ConOpVectorSet : public ConOp {
    public:
        ConOpVectorSet(ConLocation src_loc, ConLocation vector_loc, ConLocation index_loc) :

        src_loc (std::move(src_loc)), vector_loc(std::move(vector_loc)), index_loc(std::move(index_loc)) {}

    protected:
        void inner_execute(std::shared_ptr<Stack>& stack, std::vector<std::any>& arguments, std::vector<std::any>& returns,
                     std::vector<std::any>& variables,
                     ConRegs& regs) override;
        ConOpType get_type() override;

    private:
        ConLocation src_loc;
        ConLocation vector_loc;
        ConLocation index_loc;
    };
}
