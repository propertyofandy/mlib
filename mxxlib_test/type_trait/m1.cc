#include "../../type_trait/trait.hpp"
#include "trait_test_structs.hpp"
namespace mxxlib {
    int Struct1::struct2_id() { return trait<Struct2>::id; }
}

