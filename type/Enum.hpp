#ifndef ENUM_HPP_
#define ENUM_HPP_
#include <cstddef>
#include <iostream>
#include <source_location>
#include <string_view>
#include <type_traits>
#include <array>
#include <algorithm>

#include "../type_trait/trait.hpp"

namespace mxxlib {
    template <typename T>  
    struct Enumeration {
        static_assert(std::is_enum_v<T>, "T must be an enum");
        static constexpr int size = mxxlib::trait<T>::count;  
        T tag;


        using Enum = T; 

        explicit Enumeration(T v = T{}) : tag(v) {}

        Enumeration& operator++() {
            int num_value = (static_cast<int> (tag) + 1) % size;
            tag = static_cast<T>(num_value);
            return *this;
        }

        Enumeration& operator=(T v) {
            auto it = std::find(
                mxxlib::trait<T>::enumeration.begin(),
                mxxlib::trait<T>::enumeration.end(),
                v
            );
            if (it == mxxlib::trait<T>::enumeration.end()) {
                throw std::invalid_argument("Assigned value is not a valid enum member");
            }
            tag = v;
            return *this;
        }

        Enumeration& operator+=(int n) {
            int num_value = (static_cast<int> (tag) + n) % size;
            if (num_value < 0) num_value += size;  
            tag = static_cast<T>(num_value);
            return *this;
        }

        // Comparison operators
        bool operator==(const Enumeration& other) const {
            return tag == other.tag;
        }

        bool operator!=(const Enumeration& other) const {
            return !(*this == other);
        }

        bool operator<(const Enumeration& other) const {
            return static_cast<int> (tag) < static_cast<int>(other.tag);
        }

        bool operator<=(const Enumeration& other) const {
            return (*this < other) || (*this == other);
        }

        bool operator>(const Enumeration& other) const {
            return !(*this <= other);
        }

        bool operator>=(const Enumeration& other) const {
            return !(*this < other);
        }

        friend std::ostream& operator<<(std::ostream& os, const Enumeration& e) {
            int index = get_index(e); 
            if (index == -1) return os << (int)e.tag;
            return os << mxxlib::trait<T>::tag_names[index]; 
        }

        operator T() const {return tag; }
        explicit operator int() const { return static_cast<int> (tag); }

        private: 
        static constexpr size_t get_index(const Enumeration& e){ 
            int index = -1, n = 0;
            for (auto t : mxxlib::trait<T>::enumeration) {
                if(t == e.tag) index = n; 
                n++;
            }
            return index; 
        }

    };
}
#endif