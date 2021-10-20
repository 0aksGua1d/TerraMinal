#pragma once

#include <utility>
#include <vector>
#include <any>

#include "con_script/data/Stack.h"

#include "ConRegs.h"

namespace ConScript {
    class ConLocation {
    public:
        enum SECTION {
            REGS,
            VARIABLES,
            CONSTS,
            ARGUMENTS,
            RETURNS,
            STACK,
            };

        ConLocation(SECTION section, std::any value) : section(section), indexer(std::move(value)) {}

        std::any get_value(ConRegs& regs, std::vector<std::any>& variables, const std::vector<std::any>& arguments, std::vector<std::any>& returns, std::shared_ptr<Stack>& stack);
        void set_value(ConRegs& regs, std::vector<std::any>& variables, const std::vector<std::any>& arguments, std::vector<std::any>& returns, std::shared_ptr<Stack>& stack, const std::any& value);

    private:
        SECTION section;
        std::any indexer;

    private:
        std::any get_value_regs(ConRegs& regs);
        std::any get_value_variables(std::vector<std::any>& variables);
        std::any get_value_const();
        std::any get_value_arguments(const std::vector<std::any>& arguments);
        std::any get_value_returns(std::vector<std::any>& returns);
        std::any get_value_stack(std::shared_ptr<Stack>& stack);

        void set_value_regs(ConRegs& regs, const std::any& value);
        void set_value_variables(std::vector<std::any>& variables, const std::any& value);
        void set_value_arguments(std::vector<std::any>& arguments, const std::any& value);
        void set_value_returns(std::vector<std::any>& returns, const std::any& value);
        void set_value_stack(std::shared_ptr<Stack>& stack, const std::any& value);
    };
}