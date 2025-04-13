#include <gtest/gtest.h>

#include "../../type_trait/trait.hpp"

TEST(trait, enumFeatures) {
    enum class Color: char { Red, Blue, Green };

    EXPECT_EQ(mxxlib::trait<Color>::count, 3);
    EXPECT_EQ(mxxlib::trait<Color>::enumeration[0], Color::Red);
    EXPECT_EQ(mxxlib::trait<Color>::enumeration[1], Color::Blue);
    EXPECT_EQ(mxxlib::trait<Color>::enumeration[2], Color::Green);

    EXPECT_EQ(mxxlib::trait<Color>::tag_names[0], "Red");
    EXPECT_EQ(mxxlib::trait<Color>::tag_names[1], "Blue");
    EXPECT_EQ(mxxlib::trait<Color>::tag_names[2], "Green");
}