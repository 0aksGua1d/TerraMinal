#pragma once

#include "con_script/ops/ConOp.h"
#include "con_script/ConLocation.h"

namespace ConScript {
    class ConOpIntMapSet : public ConOp {
    public:
        ConOpIntMapSet(ConLocation src_loc, ConLocation map_loc, ConLocation index_loc) :
        src_loc (std::move(src_loc)), map_loc(std::move(map_loc)), index_loc(std::move(index_loc)) {}

    protected:
        void inner_execute(std::shared_ptr<Stack>& stack, const std::vector<std::any>& arguments, std::vector<std::any>& returns,
                     std::vector<std::any>& variables,
                     ConRegs& regs) override;
        ConOpType get_type() override;

    private:
        ConLocation src_loc;
        ConLocation map_loc;
        ConLocation index_loc;
    };
}
