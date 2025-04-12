#ifndef TUPLE_HELPER_HPP
#define TUPLE_HELPER_HPP
#include <any>
#include <tuple>

namespace mxxlib::_detail::reflection {

    template <class T, class... TArgs> decltype(void(T{std::declval<TArgs>()...}), std::true_type{}) test_is_braces_constructible(int);
    template <class, class...> std::false_type test_is_braces_constructible(...);
    template <class T, class... TArgs> using is_braces_constructible = decltype(test_is_braces_constructible<T, TArgs...>(0));
    
    struct any_type {
    template<class T>
    constexpr operator T(); // non explicit
    };
}

#endif