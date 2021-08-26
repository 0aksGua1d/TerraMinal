#pragma once

#include <any>

namespace ConScript {
    class ConRegs {
    public:
        enum LOCATION {
            COUNTER = 0,
            CONDITION = 1,
            BREAK = 2,
            REG_1 = 3,
            REG_2 = 4,
            REG_3 = 5,
            REG_4 = 6,
        };
        unsigned long counter = 0;
        bool condition = false;
        bool _break = false;
        std::any reg_1 = nullptr;
        std::any reg_2 = nullptr;
        std::any reg_3 = nullptr;
        std::any reg_4 = nullptr;
    };
}
