#ifndef TRAIT_HPP_
#define TRAIT_HPP_

#include <array>
#include <cstddef>
#include <type_traits>
#include "id_gen.hpp"
#include "reflect.hpp"
#include "struct_tuple_size.hpp"
#include "type_name.hpp"
#include <limits>

#include "enum_helper_functions.hpp"


namespace mxxlib {


    template <typename T, typename Enable = void>
    struct trait{        
        static constexpr int id = _detail::unique_id<T>();
        #if defined(__GNUC__) || defined(__clang__)
            static constexpr std::string_view name = _detail::type_name_to_string<T>();
        #endif
        static constexpr size_t size = sizeof(T);
        static constexpr size_t alignment = alignof(T);
    };

    template <typename T>
    struct trait <T, std::enable_if_t<std::is_enum_v<T>>>{      
        static_assert(std::is_enum_v<T>, "Type must be an enum.");
        static_assert(std::is_same_v<std::underlying_type_t<T>, char> || std::is_same_v<std::underlying_type_t<T>, unsigned char>, "Enum must have underlying type char for now.");

        static constexpr int id = _detail::unique_id<T>();
        #if defined(__GNUC__) || defined(__clang__)
            static constexpr std::string_view name = _detail::type_name_to_string<T>();
        #endif
        static constexpr size_t size = sizeof(T);
        static constexpr size_t alignment = alignof(T);

        static constexpr size_t count = _detail::enum_tag_count<T>();
        static constexpr auto enumeration =  _detail::enum_valid_values<T>();

        private:
        template <size_t... Is>
        static constexpr auto make_tag_names(std::index_sequence<Is...>) {
            return std::array<std::string_view, count>{
                _detail::enum_to_string<enumeration[Is]>()...
            };
        }
        public:
        static constexpr std::array<std::string_view, count> tag_names = make_tag_names(std::make_index_sequence<count>{});
        
    };

    template <typename T>
    struct trait <T, std::enable_if_t<std::is_integral_v<T>>>{        
        using Limit = std::numeric_limits<T>;
        static constexpr int id = _detail::unique_id<T>();
        #if defined(__GNUC__) || defined(__clang__)
            static constexpr std::string_view name = _detail::type_name_to_string<T>();
        #endif
        static constexpr size_t size = sizeof(T);
        static constexpr size_t alignment = alignof(T);
        static constexpr auto min = Limit::min(); 
        static constexpr auto max = Limit::max(); 
    };

    template <typename T> 
    struct trait <T, std::enable_if_t<std::is_class_v<T>>> {
        static constexpr int id = _detail::unique_id<T>();

        #if defined(__GNUC__) || defined(__clang__)
            static constexpr std::string_view name = _detail::type_name_to_string<T>();
        #endif
        static constexpr size_t size = sizeof(T);
        static constexpr size_t alignment = alignof(T);

        template <typename U>
        static constexpr bool child_of = std::is_base_of_v<U, T> ; // T is a base of U

        template <typename U>
        static constexpr bool parent_of = std::is_base_of_v<T, U>; // U is a base of T
        static constexpr size_t field_count = _detail::reflection::struct_to_tupple_count<T>();
        template<size_t N> struct field {
            static constexpr std::string_view name = _detail::reflection::field_name<T, N>();
            using trait = trait<std::remove_pointer_t<decltype(_detail::reflection::get_ptr<T, N>())>> ;
        };
    };

    template<typename T>
    constexpr auto type = trait<T>::id;

    template<typename T>
    constexpr auto type_of(T t){return type<T>;}

    template <typename... Ts>
    struct type_list{
        static_assert(sizeof...(Ts) > 0, "requires 1 to many arguments");

        template<typename T> 
        static constexpr bool has = (... || (mxxlib::type<T> == mxxlib::type<Ts>));
    };

}

#endif