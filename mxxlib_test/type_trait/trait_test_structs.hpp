#ifndef TRAIT_TEST_STRUCTS_HPP_
#define TRAIT_TEST_STRUCTS_HPP_

#include "../../type_trait/trait.hpp"


namespace mxxlib {
    struct Struct1;
    struct Struct2;

    struct Struct1 {
        int a;
        float b;
        int struct2_id() ;
    };
    struct Struct2 {
        int a;
        float b;
        int struct2_id() ;
    };
}

#endif // TRAIT_TEST_STRUCTS_HPP_
