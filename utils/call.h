#pragma once

template<std::size_t... Indices>
struct indices {
    using next = indices<Indices..., sizeof...(Indices)>;
};
template<std::size_t N>
struct build_indices {
    using type = typename build_indices<N - 1>::type::next;
};
template<>
struct build_indices<0> {
    using type = indices<>;
};
template<std::size_t N>
using BuildIndices = typename build_indices<N>::type;

class AnyCaster {
public:
    AnyCaster(std::any any) : inner(std::move(any)) {}

    template<typename T>
    operator T() {
        return std::any_cast<T>(this->inner);
    }

private:
    std::any inner;
};

namespace utils {

    template<typename Func, size_t... I>
    auto call_inner(Func func, const std::vector <std::any>& arguments, indices<I...>) {
        return func(AnyCaster(arguments[I])...);
    }

    template<typename RetVal, typename... Args>
    RetVal call(RetVal(* func)(Args...), const std::vector <std::any>& arguments) {
        return call_inner(func, arguments, BuildIndices<sizeof...(Args)>{});
    }
}
