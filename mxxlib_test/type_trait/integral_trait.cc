#include <gtest/gtest.h>

#include "../../type_trait/trait.hpp"

TEST(Trait, integralFeatures) {
    EXPECT_EQ(mxxlib::trait<int>::min, std::numeric_limits<int>::min());
    EXPECT_EQ(mxxlib::trait<int>::max, std::numeric_limits<int>::max());

    EXPECT_EQ(mxxlib::trait<unsigned int>::min, std::numeric_limits<unsigned int>::min());
    EXPECT_EQ(mxxlib::trait<unsigned int>::max, std::numeric_limits<unsigned int>::max());
}
