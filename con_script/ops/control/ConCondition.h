#pragma once

#include "con_script/ops/ConOp.h"
#include "con_script/ConLocation.h"

namespace ConScript {
    class ConOpCondition : public ConOp {
    public:
        explicit ConOpCondition(std::shared_ptr<std::vector<std::shared_ptr<ConOp>>> if_ops,
                                std::shared_ptr<std::vector<std::shared_ptr<ConOp>>> else_ops = nullptr) :
                                if_ops(std::move(if_ops)), else_ops(std::move(else_ops)) {}

    protected:
        void
        inner_execute(std::shared_ptr<Stack>& stack, const std::vector<std::any>& arguments, std::vector<std::any>& returns,
                      std::vector<std::any>& variables,
                      ConRegs& regs) override;

        ConOpType get_type() override;

    private:
        std::shared_ptr<std::vector<std::shared_ptr<ConOp>>> if_ops;
        std::shared_ptr<std::vector<std::shared_ptr<ConOp>>> else_ops;
    };
}
