#include "../../type_trait/trait.hpp"
#include "trait_test_structs.hpp"
#include "gtest/gtest.h"


TEST(trait, idsConsistencyAcrossFiles) {
    // Test consistency of IDs for the same type across different modules
    EXPECT_NE(mxxlib::Struct2{}.struct2_id(), mxxlib::Struct1{}.struct2_id());
}