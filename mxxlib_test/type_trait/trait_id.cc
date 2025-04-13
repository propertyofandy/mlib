#include <gtest/gtest.h>

#include <tuple>
#include <vector>

#include "../../type_trait/trait.hpp"

using namespace mxxlib; 

struct CustomStruct1 {};
struct CustomStruct2 {};
class CustomClass {
    public:
    int value;
    explicit CustomClass(int v) : value(v) {}
};

TEST(Trait, get_basic_id){
    EXPECT_EQ(trait<int>::id, 0);
    EXPECT_EQ(trait<bool>::id, 1);
    EXPECT_EQ(trait<char>::id, 2);
    EXPECT_EQ(trait<float>::id, 3);
    EXPECT_EQ(trait<double>::id, 4);
}

TEST(Trait, test_structure_ids){
    EXPECT_EQ(trait<CustomStruct1>::id, 5);
    EXPECT_EQ(trait<CustomStruct2>::id, 6);
    EXPECT_EQ(trait<CustomClass>::id, 7);
}

TEST(Trait, test_templates_ids){
    EXPECT_EQ((trait<std::pair<int, double>>::id), 8);
    EXPECT_EQ(trait<std::vector<int>>::id, 9);
    EXPECT_EQ((trait<std::tuple<int, char, float>>::id), 10);
}

TEST(Trait, test_modifier_ids){
    EXPECT_EQ(trait<int*>::id, 11);
    EXPECT_EQ(trait<int&>::id, 12);
    EXPECT_EQ(trait<const int*>::id, 13);
}

TEST(Trait, test_advanced){
    // Type aliases
    using AliasType = CustomClass;
    EXPECT_EQ(trait<AliasType>::id, trait<CustomClass>::id);
    //random modifier int 
    EXPECT_EQ(trait<volatile const int * const *>::id, 14);
}