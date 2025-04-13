#ifndef OPTIONAL_HPP_
#define OPTIONAL_HPP_

#include "Union.hpp"
namespace mxxlib {

    // Some<T> wraps a value of type T
    template <typename T>
    struct Some {
        T value;
        Some(): value(T{}) {}
        Some(const T val) : value(val) {}
        using Type = T;

        bool operator==(const Some& other) const {
            return value == other.value;
        }
    };

    // None represents no value
    struct None {
        bool operator==(const None&) const { return true; }
    };

    // Optional<T> as Union<Some<T>, None>
    template <typename T>
    using Optional = Union<Some<T>, None>;
}

#endif