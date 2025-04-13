#include <gtest/gtest.h>

#include "../../type/Enum.hpp"
enum class Color: char { Red, Green, Blue };

TEST(EnumerationTest, IncrementOperator) {
    mxxlib::Enumeration<Color> e(Color::Red);
    EXPECT_EQ(static_cast<int>(e), static_cast<int>(Color::Red));

    ++e;
    EXPECT_EQ(static_cast<int>(e), static_cast<int>(Color::Green));

    e += 1;
    EXPECT_EQ(static_cast<int>(e), static_cast<int>(Color::Blue));
}

TEST(EnumerationTest, AssignmentOperator) {
    mxxlib::Enumeration<Color> e;
    e = Color::Blue;
    EXPECT_EQ(static_cast<int>(e), static_cast<int>(Color::Blue));
}

TEST(EnumerationTest, ComparisonOperators) {
    mxxlib::Enumeration<Color> e1(Color::Red);
    mxxlib::Enumeration<Color> e2(Color::Red);
    mxxlib::Enumeration<Color> e3(Color::Green);
    EXPECT_TRUE(e1 == e2);
    EXPECT_TRUE(e1 != e3);
    EXPECT_TRUE(e1 < e3);
}