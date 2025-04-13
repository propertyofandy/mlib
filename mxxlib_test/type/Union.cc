#include <gtest/gtest.h>

#include "../../type/Union.hpp"


TEST(UnionTest, IntConstructor) {
    // Create a Union holding an int.
    mxxlib::Union<int, double> u(42);
    EXPECT_TRUE(u.template is<int>());
    EXPECT_EQ(u.template get<int>(), 42);
}

TEST(UnionTest, DoubleConstructor) {
    // Create a Union holding a double.
    mxxlib::Union<int, double> u(3.14);
    EXPECT_TRUE(u.template is<double>());
    EXPECT_DOUBLE_EQ(u.template get<double>(), 3.14);
}

TEST(UnionTest, CopyConstructor) {
    mxxlib::Union<int, double> u1(100);
    mxxlib::Union<int, double> u2(u1);
    EXPECT_TRUE(u2.template is<int>());
    EXPECT_EQ(u2.template get<int>(), 100);
}

TEST(UnionTest, MoveConstructor) {
    mxxlib::Union<int, double> u1(50);
    mxxlib::Union<int, double> u2(std::move(u1));
    EXPECT_TRUE(u2.template is<int>());
    EXPECT_EQ(u2.template get<int>(), 50);
}