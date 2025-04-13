#ifndef UNION_HPP
#define UNION_HPP

#include "../type_trait/trait.hpp"
#include <type_traits>

namespace mxxlib {


//used to determine max alignment and size at compile time
template<typename... Ts>
struct MaxTraits;

template<typename T>
struct MaxTraits<T> {
    static constexpr size_t max_size = sizeof(T);
    static constexpr size_t max_align = alignof(T);
};

template<typename T, typename... Rest>
struct MaxTraits<T, Rest...> {
    static constexpr size_t rest_size = MaxTraits<Rest...>::max_size;
    static constexpr size_t rest_align = MaxTraits<Rest...>::max_align;
    static constexpr size_t max_size = sizeof(T) > rest_size ? sizeof(T) : rest_size;
    static constexpr size_t max_align = alignof(T) > rest_align ? alignof(T) : rest_align;
};

// call destroctor on some T
template<typename T>
void destroy(void* data) { reinterpret_cast<T*>(data)->~T(); }


// find type in Rest... that is T if found execute fn<T>()
template<typename... Ts>
struct TypeSelector;
/// @brief matches T against a list of types if it is found we execute the associated function
/// @tparam T 
/// @tparam ...Rest 
template<typename T, typename... Rest>
struct TypeSelector<T, Rest...> {
    template<typename F>
    static void withType(size_t id, void* data, F&& f) {
        if (id == mxxlib::type<T>) {
            f(T{}, data);
        } else {
            TypeSelector<Rest...>::withType(id, data, f);
        }
    }
};

template<typename T>
struct TypeSelector<T> {
    template<typename F>
    static void withType(size_t id, void* data, F&& f) {
        if (id == mxxlib::type<T>) {
            f(T{}, data);
        }
    }
};

template<typename... Ts> constexpr bool all_are_default_constructable(){
    return (std::is_default_constructible_v<Ts> && ...); 
}

template<typename... Ts> requires (all_are_default_constructable<Ts...>())
struct Union {

    template<typename T>
    requires mxxlib::type_list<Ts...>::template has<T>
    explicit Union(const T& item) : type_id(mxxlib::type<T>) {
        new (data) T(item); // Placement new
    }

    template<typename T>
    requires mxxlib::type_list<Ts...>::template has<T>
    explicit Union(T&& item) : type_id(mxxlib::type<T>) {
        new (data) T(std::move(item)); // Placement new
    }
    Union(const Union& other) : type_id(other.type_id) {
        TypeSelector<Ts...>::withType(type_id, other.data, [&](auto t, void* d) {
            using CurrentT = std::decay_t<decltype(t)>;
            new (data) CurrentT(*reinterpret_cast<CurrentT*>(d));
        });
    }

    // Move constructor
    Union(Union&& other) : type_id(other.type_id) {
        TypeSelector<Ts...>::withType(type_id, other.data, [&](auto t, void* d) {
            using CurrentT = std::decay_t<decltype(t)>;
            new (data) CurrentT(std::move(*reinterpret_cast<CurrentT*>(d)));
        });
        other.type_id = 0; // Invalidate other
    }

    ~Union(){
        TypeSelector<Ts...>::withType(type_id, data, [](auto t, void* d) {
            using CurrentT = decltype(t);
            destroy<CurrentT>(d);
        });
    }

    template<typename T>
    requires mxxlib::type_list<Ts...>::template has<T>
    T get() const {
        if(type_id == mxxlib::type<T>)
            return *reinterpret_cast<const T*>(data);
        else 
            return T{}; 
    }

    template<typename T>
    bool is() const {
        return type_id == mxxlib::type<T>;
    }

    size_t type() const {
        return type_id;
    }

private:
    static constexpr size_t max_align = MaxTraits<Ts...>::max_align;
    static constexpr size_t max_size  = MaxTraits<Ts...>::max_size;
    alignas(max_align) char data[max_size];
    size_t type_id;
};

}
#endif