#pragma once

#include <utility>

#include "con_script/ops/ConOp.h"
#include "con_script/ConLocation.h"

namespace ConScript {
    class ConOpCall : public ConOp {
    public:
        ConOpCall(ConLocation func_name_loc, std::vector<ConLocation> args, std::vector<ConLocation> returns) :
                func_name_loc(std::move(func_name_loc)), args(std::move(args)), returns(std::move(returns)) {}

    protected:
        void inner_execute(std::shared_ptr<Stack>& stack, const std::vector<std::any>& parent_func_args,
                     std::vector<std::any>& parent_func_returns,
                     std::vector<std::any>& variables,
                     ConRegs& regs) override;
        ConOpType get_type() override;

    private:
        ConLocation func_name_loc;
        std::vector<ConLocation> args;
        std::vector<ConLocation> returns;
    };
}
