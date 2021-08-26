#include <type_traits>

#include "LambdaLogFilter.h"

template<typename filter>
template<typename... Args>
LambdaLogFilter<filter>::LambdaLogFilter(Args... args) : _filter(args...) {}

template<typename filter>
bool LambdaLogFilter<filter>::should_log(const Log& log) {
    if (std::is_pointer<filter>::value) {
        return this->_filter->should_log(log);
    } else {
        return this->_filter.should_log(log);
    }
}
