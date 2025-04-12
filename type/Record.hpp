#ifndef RECORD_HPP_
#define RECORD_HPP_

#include <tuple>
#include "../type_trait/trait.hpp"

namespace mxxlib {
    template <typename... Ts>
    class Record {
    private:
        std::tuple<Ts...> data;

        using types = mxxlib::type_list<Ts...>;

    public:
        // Default constructor
        Record() = default;

        // Constructor for initializing with values
        Record(Ts... args) : data(args...) {}

        // Get non-const reference to T
        template <typename T> requires types::template has<T>
        T& get() {
            return std::get<T>(data);
        }

        // Get const reference to T
        template <typename T> requires types::template has<T>
        const T& get() const {
            return std::get<T>(data);
        }
    };
}
#endif

