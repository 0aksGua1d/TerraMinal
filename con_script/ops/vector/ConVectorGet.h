#pragma once

#include "con_script/ops/ConOp.h"
#include "con_script/ConLocation.h"

namespace ConScript {
    class ConOpVectorGet : public ConOp {
    public:
        ConOpVectorGet(ConLocation vector_loc, ConLocation index_loc, ConLocation dest_loc) :
                vector_loc(std::move(vector_loc)), index_loc(std::move(index_loc)), dest_loc(std::move(dest_loc)) {}

    protected:
        void inner_execute(std::shared_ptr<Stack>& stack, std::vector<std::any>& arguments, std::vector<std::any>& returns,
                     std::vector<std::any>& variables,
                     ConRegs& regs) override;
        ConOpType get_type() override;

    private:
        ConLocation vector_loc;
        ConLocation index_loc;
        ConLocation dest_loc;
    };
}
