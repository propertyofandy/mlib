#include "../../type_trait/trait.hpp"
#include "trait_test_structs.hpp"

namespace mxxlib {
    constexpr auto v = trait<int>::id; 
    int Struct2::struct2_id() { return trait<Struct2>::id; }
    
}