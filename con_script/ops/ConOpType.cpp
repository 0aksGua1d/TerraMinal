#include "ConOpType.h"

namespace ConScript {
    std::map<ConOpType, std::string> ConOpNames = {
            {ConOpType::ConCall,           "ConCall"},
            {ConOpType::ConCondition,      "ConCondition"},
            {ConOpType::ConMove,           "ConMove"},
            {ConOpType::ConFunc,           "ConFunc"},
            {ConOpType::ConIntMapGet,      "ConIntMapGet"},
            {ConOpType::ConIntMapSet,      "ConIntMapSet"},
            {ConOpType::ConEnterScope,     "ConEnterScope"},
            {ConOpType::ConEnterWeakScope, "ConEnterWeakScope"},
            {ConOpType::ConExistVar,       "ConExistVar"},
            {ConOpType::ConExitScope,      "ConExitScope"},
            {ConOpType::ConVectorGet,      "ConVectorGet"},
            {ConOpType::ConVectorSet,      "ConVectorSet"},
            };
}
