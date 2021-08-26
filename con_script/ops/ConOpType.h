#pragma once

#include <map>

namespace ConScript {
    enum class ConOpType {
        ConCall,
        ConCondition,
        ConMove,

        ConFunc,

        ConIntMapGet,
        ConIntMapSet,

        ConEnterScope,
        ConEnterWeakScope,
        ConExistVar,
        ConExitScope,

        ConVectorGet,
        ConVectorSet,

        ConOpAdd,
    };

    extern std::map<ConOpType, std::string> ConOpNames;
}
