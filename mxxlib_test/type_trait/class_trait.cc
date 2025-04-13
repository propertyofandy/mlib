#include <gtest/gtest.h>

#include "../../type_trait/trait.hpp"

class Base {};
class Derived : public Base {
    public:
    Derived(){}
    Derived(int _x, double _y): x{_x}, y{_y}{}
        int x;
        double y;
};

TEST(Trait, classFeatures) {
    EXPECT_TRUE(mxxlib::trait<Derived>::child_of<Base>);
    EXPECT_FALSE(mxxlib::trait<Base>::child_of<Derived>);
    EXPECT_TRUE(mxxlib::trait<Base>::parent_of<Derived>);
    EXPECT_EQ(mxxlib::trait<Derived>::field_count, 2);

    EXPECT_EQ(mxxlib::trait<Derived>::field<0>::name, "x");
    EXPECT_EQ(mxxlib::trait<Derived>::field<1>::name, "y");

    EXPECT_EQ(mxxlib::trait<Derived>::field<0>::trait::size, sizeof(int));
    EXPECT_EQ(mxxlib::trait<Derived>::field<1>::trait::size, sizeof(double));

}
