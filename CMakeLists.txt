cmake_minimum_required(VERSION 3.30.0)
project(mxxlib VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)          
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

add_library(mxxlib INTERFACE
    type_trait/id_gen.hpp 
    type_trait/enum_helper_functions.hpp 
    type_trait/reflect.hpp 
    type_trait/struct_tuple_size.hpp 
    type_trait/trait.hpp 
    type_trait/tuple_helper.hpp 
    type_trait/tuple_pointer.hpp 
    type_trait/type_name.hpp 
    type/Union.hpp 
    type/Record.hpp 
    type/Enum.hpp 
)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(mxxlib_test)

include(GoogleTest)
