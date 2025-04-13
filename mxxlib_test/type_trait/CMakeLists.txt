cmake_minimum_required(VERSION 3.30.0)
project(type_trait_test)

enable_testing()

add_executable(type_name_test typename.cc)
target_link_libraries(type_name_test 
    mxxlib 
    gtest
    gtest_main
)
add_test(NAME TypeToString COMMAND type_name_test)


add_executable(trait_id_test trait_id.cc)
target_link_libraries(trait_id_test 
    mxxlib 
    gtest
    gtest_main
)
add_test(NAME TraitIDTest COMMAND trait_id_test )

add_executable(trait_data_test trait_data.cc)
target_link_libraries(trait_data_test 
    mxxlib 
    gtest
    gtest_main
)
add_test(NAME TraitDataTest COMMAND trait_data_test )

add_executable(test_ids_consistency test_ids_consistency.cc m1.cc m2.cc)
target_link_libraries(test_ids_consistency PRIVATE gtest gtest_main)
add_test(NAME test_ids_consistency_test COMMAND test_ids_consistency )

add_executable(trait_enum_test enum_traits.cc)
target_link_libraries(trait_enum_test mxxlib gtest gtest_main)
add_test(NAME TraitEnumTest COMMAND trait_enum_test )

add_executable(trait_class_test class_trait.cc)
target_link_libraries(trait_class_test 
    mxxlib 
    gtest
    gtest_main
)
add_test(NAME TraitClassTest COMMAND trait_class_test )

add_executable(trait_int_test integral_trait.cc)
target_link_libraries(trait_int_test 
    mxxlib 
    gtest
    gtest_main
)
add_test(NAME TraitIntTest COMMAND trait_int_test )