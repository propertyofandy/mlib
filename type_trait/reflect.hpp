#ifndef REFLECT_HPP
#define REFLECT_HPP
#include "tuple_pointer.hpp"
#include <source_location>
#include <string_view>


namespace mxxlib::_detail::reflection {
    // Helper to wrap a type for compile-time tricks
    template <typename T>
    struct wrapper {
        explicit constexpr wrapper(const T& v) : value(v) {}
        T value;
        static wrapper<T> fake;  // Dummy instance
    };
    template <typename T>
    inline wrapper<T> wrapper<T>::fake = wrapper<T>(T{});

    
    // Get pointer to the N-th field at compile time
    template <typename T, std::size_t N>
    consteval auto get_ptr() noexcept {
        constexpr auto ptr_tuple = to_ptr_tuple(wrapper<T>::fake.value);
        return std::get<N>(ptr_tuple);
    }

    // Get function name as a string (compiler-dependent)
    template <typename T, auto Ptr>
    consteval std::string_view get_function_name() {
        #if defined(__clang__) || defined(__GNUC__)
                return std::string_view{std::source_location::current().function_name()};
        #else
                return std::string_view{__FUNCSIG__};  // MSVC
        #endif
    }

    // Deduce field name by parsing function name
    template <typename T, auto Ptr>
    consteval std::string_view get_field_name() {
        struct field_name_detector {
            void* dummy;
        };

        constexpr auto detector_name = get_function_name<field_name_detector, &field_name_detector::dummy>();
        constexpr auto dummy_pos = detector_name.find("dummy");
        constexpr auto suffix = detector_name.substr(dummy_pos + 5);  // "dummy" is 5 chars
        constexpr auto begin_sentinel = detector_name[dummy_pos - 1];  // Typically '.'

        constexpr auto field_name_raw = get_function_name<T, Ptr>();
        const auto last = field_name_raw.rfind(suffix);
        const auto begin = field_name_raw.rfind(begin_sentinel, last - 1) + 1;

        assert(begin < field_name_raw.size() && last <= field_name_raw.size() && begin < last);
        return field_name_raw.substr(begin, last - begin);
    }

    // Public interface for field name

    #ifdef __clang__
        template <typename T, std::size_t N> constexpr std::string_view field_name (){ 
            constexpr auto str =  get_field_name<T, get_ptr<T, N>()>();
            constexpr auto in = str.find("value.");
            if constexpr (in != -1)
                return std::string_view{str.begin()+in+6, str.end()};
            else 
                return std::string_view{str.begin()+55, str.end()};
        }
    #elif  __GNUC__
        template <typename T, std::size_t N> constexpr std::string_view field_name (){ 
            constexpr auto str =  get_field_name<T, get_ptr<T, N>()>();
            return std::string_view{str.begin(), str.end()-1};
        }
    #endif
}  // namespace detail

#endif 