#pragma once

#include <memory>
#include <vector>

#include "utils/IdGenerator.h"
#include "ops/ConOp.h"

namespace ConScript {
    class Stack;

    class ConFunction {
    public:
        ConFunction(std::shared_ptr<std::vector<std::shared_ptr<ConOp>>> ops, std::vector<std::any> init_static_data,
                    size_t extra_vars, size_t arguments_count, size_t return_count);

        void call(const std::vector<std::any>& arguments, std::vector<std::any>& returns, std::shared_ptr<Stack> stack);

//    private:
        static IdGenerator generator;

    private:
        std::shared_ptr<std::vector<std::shared_ptr<ConOp>>> ops;
        std::vector<std::any> static_data;
        size_t extra_vars;
        size_t arguments_count;
        size_t return_count;
    };
}
