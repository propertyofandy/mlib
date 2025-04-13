
#include <gtest/gtest.h>
#include "../../type_trait/trait.hpp"

// Test fixture for fundamental types

using namespace mxxlib;

TEST(Trait, SizeAndAlignment) {
    EXPECT_EQ(trait<int>::size, sizeof(int));
    EXPECT_EQ(trait<int>::alignment, alignof(int));

    EXPECT_EQ(trait<double>::size, sizeof(double));
    EXPECT_EQ(trait<double>::alignment, alignof(double));

    EXPECT_EQ(trait<char>::size, sizeof(char));
    EXPECT_EQ(trait<char>::alignment, alignof(char));
}


TEST(Trait, SizeAndAlignmentStructs) {
    struct CustomStruct1 { int a; double b; };
    EXPECT_EQ(trait<CustomStruct1>::size, sizeof(CustomStruct1));
    EXPECT_EQ(trait<CustomStruct1>::alignment, alignof(CustomStruct1));

    class CustomClass {
    public:
        char a;
        int b;
        double c;
    };
    EXPECT_EQ(trait<CustomClass>::size, sizeof(CustomClass));
    EXPECT_EQ(trait<CustomClass>::alignment, alignof(CustomClass));
}



TEST(Trait, SizeAndAlignmentTemplates) {
    EXPECT_EQ((trait<std::pair<int, double>>::size), sizeof(std::pair<int, double>));
    EXPECT_EQ((trait<std::pair<int, double>>::alignment), alignof(std::pair<int, double>));

    EXPECT_EQ(trait<std::vector<int>>::size, sizeof(std::vector<int>));
    EXPECT_EQ(trait<std::vector<int>>::alignment, alignof(std::vector<int>));
}
