#pragma once
#include <string>
#include <sstream>

class WrongDataTypeError : public std::exception {
public:
    WrongDataTypeError(const std::string& requested_data_type, const std::string& existing_data_type) : requested_data_type(requested_data_type), existing_data_type(existing_data_type) {}
    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override {
        std::stringstream stringstream;
        stringstream << "Requested: " << requested_data_type << std::endl << "Existing: " << existing_data_type;
        return stringstream.str().c_str();
    }
private:
    std::string requested_data_type;
    std::string existing_data_type;
};
