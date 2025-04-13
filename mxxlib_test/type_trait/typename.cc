#include <gtest/gtest.h>
#include "../../type_trait/type_name.hpp"
#include <string>
struct Person{};
template <typename T> struct A{};
template <typename... T> struct B{}; 

namespace aa {
    struct C {};
}

TEST(typeName, getName){
    EXPECT_EQ(mxxlib::_detail::type_name_to_string<int>(), "int");
    EXPECT_EQ(mxxlib::_detail::type_name_to_string<Person>(), "Person");
    EXPECT_EQ(mxxlib::_detail::type_name_to_string<A<Person>>(), "A<Person>");
    EXPECT_EQ(mxxlib::_detail::type_name_to_string<aa::C>(), "aa::C");
}