#pragma once

#include <utility>
#include <map>
#include <any>

#include "../ConFunction.h"

namespace ConScript {
    class NoSuchVariable : public std::exception {
    public:
        NoSuchVariable(const std::wstring& name) : name() {
            size_t size = (wcslen(name.c_str()) + 1) * sizeof(wchar_t);
            auto buffer = std::unique_ptr<char>(new char[size]);
#ifdef __STDC_LIB_EXT1__
            size_t converted;
            std::wcstombs_s(&converted, buffer, size, name.c_str(), size);
#else
            std::wcstombs(buffer.get(), name.c_str(), size);
#endif
            this->name = std::string(buffer.get()).substr(0);
        }
        [[nodiscard]] const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override { return name.data(); }
    private:
        std::string name;
    };

    class Scope {
    public:
        Scope() : functions(std::make_shared<std::map<std::wstring, std::shared_ptr<ConFunction>>>()), variables() {}
        explicit Scope(std::shared_ptr<std::map<std::wstring, std::shared_ptr<ConFunction>>> functions) : functions(std::move(functions)), variables() {}
    public:
        std::shared_ptr<std::map<std::wstring, std::shared_ptr<ConFunction>>> functions;
        std::map<std::wstring, std::any> variables;
    };
}
