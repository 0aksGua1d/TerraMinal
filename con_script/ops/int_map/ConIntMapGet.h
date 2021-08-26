#pragma once

#include "con_script/ops/ConOp.h"
#include "con_script/ConLocation.h"

namespace ConScript {
    class ConOpIntMapGet : public ConOp {
    public:
        ConOpIntMapGet(ConLocation map_loc, ConLocation index_loc, ConLocation dest_loc) :
        map_loc(std::move(map_loc)), index_loc(std::move(index_loc)), dest_loc(std::move(dest_loc)) {}

    protected:
        void inner_execute(std::shared_ptr<Stack>& stack, std::vector<std::any>& arguments, std::vector<std::any>& returns,
                     std::vector<std::any>& variables,
                     ConRegs& regs) override;
        ConOpType get_type() override;

    private:
        ConLocation map_loc;
        ConLocation index_loc;
        ConLocation dest_loc;
    };
}
