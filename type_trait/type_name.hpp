#ifndef TYPE_NAME_HPP
#define TYPE_NAME_HPP

#include <source_location>
#include <string_view>


namespace  mxxlib::_detail {


    #ifdef __clang__
        template <typename T> constexpr auto func_name() {
            return std::string_view{std::source_location::current().function_name()};
        }

        template <typename T> constexpr std::string_view type_name_to_string() {
            constexpr std::string_view functionName = func_name<T>();
            return {functionName.begin() + 51, functionName.end() - 1};
        }

    #elif  __GNUC__
        template <typename T> constexpr auto func_name() {
            return std::string_view{ __PRETTY_FUNCTION__ };
        }

        template <typename T> constexpr std::string_view type_name_to_string() {
            constexpr std::string_view functionName = func_name<T>();
            return {functionName.begin()+54, functionName.end()-1};
        }
    #endif






}
#endif 