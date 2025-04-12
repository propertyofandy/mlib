#ifndef ID_GEN_HPP
#define ID_GEN_HPP

namespace mxxlib::_detail {
    template<auto Id>
    struct _counter {
        using tag = _counter;

        struct generator {
            friend consteval auto is_defined(tag)
            { return true; }
        };

        // turn off gcc warning for this item 
        #ifdef __GNUC__
            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wnon-template-friend"
        #endif
        friend consteval auto is_defined(tag);
        #ifdef __GNUC__
            #pragma GCC diagnostic pop
        #endif
        // GCC warning enabled

        template<typename Tag = tag, auto = is_defined(Tag{})>
        static consteval auto exists(auto)
        { return true; }

        static consteval auto exists(...)
        { return generator(), false; }
    };

    template<typename T, auto Id = int{}>
    constexpr auto unique_id() {
        if constexpr (_counter<Id>::exists(Id)) {
            return unique_id<T, Id + 1>();
        } else {
            return Id;
        }
    }
}


#endif