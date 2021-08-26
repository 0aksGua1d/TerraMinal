#pragma once

#include <exception>
#include <sstream>

#include "utils/string_converter.h"

class VariableNotFound : public std::exception {
public:
    explicit VariableNotFound(const std::string& searched_var) {
        this->searched_var = generate_message(searched_var);
    }

    explicit VariableNotFound(const std::wstring& searched_var) {
        this->searched_var = generate_message(string_converter.to_bytes(searched_var));
    }

protected:
    [[nodiscard]] const char* what() const noexcept override {
        return searched_var.c_str();
    }

private:
    static std::string generate_message(const std::string& searched_var) {
        std::stringstream ss;
        ss << "Variable not func: " << searched_var;
        return ss.str();
    }
    std::string searched_var{};
};
