#ifndef ENUM_HELPER_FUNCTIONS
#define ENUM_HELPER_FUNCTIONS


#include <type_traits>
#include "type_name.hpp" 
#include <limits>

namespace mxxlib::_detail {
    #ifdef __clang__
        template <auto E> constexpr bool valid_enum_tag(){
            using T = std::remove_cv_t<std::decay_t<decltype(E)>>;
            constexpr auto str = std::string_view {std::source_location::current().function_name()};
            constexpr auto val = str.find( type_name_to_string<T>() );
            if constexpr(str[val-1] != '(')
                return true; 
            else return false; 
        }
    #elif __GNUC__
        template <auto E> constexpr bool valid_enum_tag(){
            using T = std::remove_cv_t<std::decay_t<decltype(E)>>;
            constexpr auto str = std::string_view {__PRETTY_FUNCTION__ };
            constexpr size_t n = str.find("E = ")+4;
            if constexpr(str[n] == '('){
                return false;
            }
            else
                return true;
        }
    #endif
    #ifdef __clang__
        template <auto E> constexpr std::string_view enum_to_string(){
            using T = std::remove_cv_t<std::decay_t<decltype(E)>>;
            constexpr auto str = std::string_view {std::source_location::current().function_name()};
            constexpr size_t beg = type_name_to_string<T>().size();
            constexpr auto val = str.find( type_name_to_string<T>() );
            return std::string_view{str.begin()+val+beg+2, str.end()-1};
        }
    #elif __GNUC__
        template <auto E> constexpr std::string_view enum_to_string(){
            using T = std::remove_cv_t<std::decay_t<decltype(E)>>;
            constexpr auto str = std::string_view {__PRETTY_FUNCTION__ };
            constexpr size_t beg = type_name_to_string<T>().size();
            constexpr auto val = str.find( type_name_to_string<T>() );
            constexpr size_t e =  str.rfind(";");    
            return std::string_view{str.begin()+val+beg+2, str.end() - (str.size()-e)};
        }
    #endif
template <typename T, long int start, long int end> constexpr size_t get_valid_enum_count(){
    
    if constexpr (start >= end) return 0;
    else if constexpr (valid_enum_tag<static_cast<T>(start)>()){
        return get_valid_enum_count<T, start+1, end>()+1;
    }
    else return get_valid_enum_count<T, start+1, end>();
} 

template<typename T> constexpr size_t enum_tag_count(){
    using Enum = std::underlying_type_t<T>;
    using Limit = std::numeric_limits<Enum>;
    if constexpr(Limit::max() == 0){
        return 0;
    }
    else
        return get_valid_enum_count<T, static_cast<long int>(Limit::min()), static_cast<long int>(Limit::max())>();
} 

template <typename T, long int start, long int end, size_t index, size_t N>
constexpr auto get_valid_enum_array_impl(std::array<T, N>& arr) {
    if constexpr (start < end && index < N) {
        if constexpr (valid_enum_tag<static_cast<T>(start)>()) {
            arr[index] = static_cast<T>(start);
            if constexpr (index + 1 < N) {
                return get_valid_enum_array_impl<T, start + 1, end, index + 1, N>(arr);
            }
        }
        else {
            return get_valid_enum_array_impl<T, start + 1, end, index, N>(arr);
        }
    }
    return arr;
}

// Wrapper to initialize the array
template <typename T, long int start, long int end>
constexpr auto get_valid_enum_array() {
    constexpr size_t count = get_valid_enum_count<T, start, end>();
    std::array<T, count> arr{};
    if constexpr (count > 0) {
        return get_valid_enum_array_impl<T, start, end, 0, count>(arr);
    }
    return arr;
}

// Public interface to get valid enum values
template <typename T>
constexpr auto enum_valid_values() {
    using UnderlyingType = std::underlying_type_t<T>;
    using Limit = std::numeric_limits<UnderlyingType>;
    return get_valid_enum_array<T, static_cast<long int>(Limit::min()), static_cast<long int>(Limit::max())>();
}
}


#endif