#include "ConLocation.h"

namespace ConScript {
    std::any ConLocation::get_value_regs(ConRegs& regs) {
        auto id = std::any_cast<ConRegs::LOCATION>(this->indexer);
        switch (id) {
            case ConRegs::LOCATION::COUNTER:
                return std::move((std::any)regs.counter);
            case ConRegs::LOCATION::CONDITION:
                return std::move((std::any)regs.condition);
            case ConRegs::LOCATION::BREAK:
                return std::move((std::any)regs._break);
            case ConRegs::LOCATION::REG_1:
                return std::move((std::any)regs.reg_1);
            case ConRegs::LOCATION::REG_2:
                return std::move((std::any)regs.reg_2);
            case ConRegs::LOCATION::REG_3:
                return std::move((std::any)regs.reg_3);
            case ConRegs::LOCATION::REG_4:
                return std::move((std::any)regs.reg_4);
            default:
                return nullptr;
        }
    }

    std::any ConLocation::get_value_variables(std::vector<std::any>& variables) {
        auto index = std::any_cast<int>(this->indexer);
        return std::move(variables[index]);
    }

    std::any ConLocation::get_value_const() {
        return this->indexer;
    }

    std::any ConLocation::get_value_arguments(const std::vector<std::any>& arguments) {
        auto index = std::any_cast<int>(this->indexer);
        return arguments[index];
    }

    std::any ConLocation::get_value_returns(std::vector<std::any>& returns) {
        auto index = std::any_cast<int>(this->indexer);
        return std::move(returns[index]);
    }

    std::any ConLocation::get_value_stack(std::shared_ptr<Stack>& stack) {
        auto name = std::any_cast<std::wstring>(this->indexer);
        std::any ret = stack->get_var(name);
        return ret;
    }


    std::any ConLocation::get_value(ConRegs& regs, std::vector<std::any>& variables, const std::vector<std::any>& arguments,
                                    std::vector<std::any>& returns, std::shared_ptr<Stack>& stack) {
        switch (this->section) {
            case SECTION::REGS:
                return std::move(this->get_value_regs(regs));
            case SECTION::VARIABLES:
                return std::move(this->get_value_variables(variables));
            case SECTION::CONSTS:
                return std::move(this->get_value_const());
            case SECTION::ARGUMENTS:
                return std::move(this->get_value_arguments(arguments));
            case SECTION::RETURNS:
                return std::move(this->get_value_returns(returns));
            case SECTION::STACK:
                return std::move(this->get_value_stack(stack));
            default:
                return nullptr;
        }
    }

    void ConLocation::set_value_regs(ConRegs& regs, const std::any& value) {
        auto id = std::any_cast<ConRegs::LOCATION>(this->indexer);
        switch (id) {
            case ConRegs::LOCATION::COUNTER:
                regs.counter = std::any_cast<unsigned long>(value);
                break;
            case ConRegs::LOCATION::CONDITION:
                regs.condition = std::any_cast<bool>(value);
                break;
            case ConRegs::LOCATION::BREAK:
                regs._break = std::any_cast<bool>(value);
                break;
            case ConRegs::LOCATION::REG_1:
                regs.reg_1 = value;
                break;
            case ConRegs::LOCATION::REG_2:
                regs.reg_2 = value;
                break;
            case ConRegs::LOCATION::REG_3:
                regs.reg_3 = value;
                break;
            case ConRegs::LOCATION::REG_4:
                regs.reg_4 = value;
                break;
        }
    }

    void ConLocation::set_value_variables(std::vector<std::any>& variables, const std::any& value) {
        auto index = std::any_cast<int>(this->indexer);
        variables[index] = value;
    }

    void ConLocation::set_value_returns(std::vector<std::any>& returns, const std::any& value) {
        auto index = std::any_cast<int>(this->indexer);
        returns[index] = value;
    }

    void ConLocation::set_value_stack(std::shared_ptr<Stack>& stack, const std::any& value) {
        auto name = std::any_cast<std::wstring>(this->indexer);
        stack->set_var(name, value);
    }

    void ConLocation::set_value(ConRegs& regs, std::vector<std::any>& variables, const std::vector<std::any>& arguments,
                                std::vector<std::any>& returns, std::shared_ptr<Stack>& stack, const std::any& value) {
        switch (this->section) {
            case SECTION::REGS:
                this->set_value_regs(regs, value);
                break;
            case SECTION::VARIABLES:
                this->set_value_variables(variables, value);
                break;
            case SECTION::CONSTS:
                break;
            case SECTION::RETURNS:
                this->set_value_returns(returns, value);
                break;
            case SECTION::STACK:
                this->set_value_stack(stack, value);
                break;
            case SECTION::ARGUMENTS:
                // arguments are constant
                break;
        }
    }
}