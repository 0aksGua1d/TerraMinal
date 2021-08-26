#pragma once

#include "con_script/ops/ConOp.h"
#include "con_script/ConLocation.h"

namespace ConScript {
    template<typename Func>
    class ConOpFunc : public ConOp {
    public:
        ConOpFunc(Func func, std::vector<ConLocation> arg_locs, ConLocation ret_loc) : func(func),
                                                                                       arg_locs(std::move(arg_locs)),
                                                                                       ret_loc(std::move(ret_loc)) {}
    protected:
        void inner_execute(std::shared_ptr<Stack>& stack, std::vector<std::any>& arguments, std::vector<std::any>& returns,
                     std::vector<std::any>& variables,
                     ConRegs& regs) override;
        ConOpType get_type() override;

    private:
        Func func;
        std::vector<ConLocation> arg_locs;
        ConLocation ret_loc;
    };
}
