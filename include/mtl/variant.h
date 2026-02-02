///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2026 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file variant.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 02-02-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_VARIANT_H
#define MTL_VARIANT_H

#include <cstddef>

#include "utility.h"
#include "largest.h"
#include "type_traits.h"

namespace mtl
{
struct monostate {};

namespace private_variant
{
template<size_t I>
struct null_type { static constexpr size_t index = I; };

template<typename A, typename S>
struct storage_type
{
    alignas(A) unsigned char data[sizeof(S)];
};

template <size_t I, typename... Ts> struct destroyer;

template <size_t I, typename T, typename... Rest>
struct destroyer<I, T, Rest...>
{
    static void destroy(size_t index, void* storage)
    {
        if (index == I)
            reinterpret_cast<T*>(storage)->~T();
        else
            destroyer<I + 1, Rest...>::destroy(index, storage);
    }
};

template <size_t I>
struct destroyer<I>
{
    static void destroy(size_t, void*) {}
};
}

template<typename T1,
         typename T2 = private_variant::null_type<2>,
         typename T3 = private_variant::null_type<3>,
         typename T4 = private_variant::null_type<4>,
         typename T5 = private_variant::null_type<5>,
         typename T6 = private_variant::null_type<6>,
         typename T7 = private_variant::null_type<7>,
         typename T8 = private_variant::null_type<8> >
class variant
{
    public:
    using index_type    = size_t;
    using largest_type  = largest_type_t<T1, T2, T3, T4, T5, T6, T7, T8>;
    using largest_align = typename largest_alignment<T1, T2, T3, T4, T5, T6, T7, T8>::type;
    using storage_type  = private_variant::storage_type<largest_align, largest_type>;
    
    // Random value chosen by the universe upon its creation.
    static constexpr index_type unsuported_type_id = 12876387;
    
    template <typename T>
    struct type_id_lookup
    {
        static const index_type value = is_same_v<T, T1> ? 0 :
                                        is_same_v<T, T2> ? 1 :
                                        is_same_v<T, T3> ? 2 :
                                        is_same_v<T, T4> ? 3 :
                                        is_same_v<T, T5> ? 4 :
                                        is_same_v<T, T6> ? 5 :
                                        is_same_v<T, T7> ? 6 :
                                        is_same_v<T, T8> ? 7 :
                                        unsuported_type_id;
    };
    
    template<typename T>
    struct is_suported : integral_constant<bool, type_id_lookup<T>::value != unsuported_type_id> {};
    
    template <typename T>
    static constexpr bool is_suported_v = is_suported<T>::value;
    
    // All types of variant are friends.
    template <typename V1, typename V2, typename V3, typename V4,
              typename V5, typename V6, typename V7, typename V8>
    friend class variant;
    
    // Assignment
    
    constexpr variant() : _hold_index(unsuported_type_id) {}
    
    ~variant() { reset(); }
    
    template <typename T, typename... Args>
    void emplace(Args&&... args)
    {
        static_assert(is_suported_v<T>, "T is not a alternative to this variant");
        
        this->reset();
        new (_storage.data) T(forward<Args>(args)...);
        this->_hold_index = type_id_lookup<T>::value;
    }
    
    template<typename T, typename U = remove_reference_t<T>>
    constexpr variant(T&& value) : _hold_index(unsuported_type_id)
    {
        this->emplace<U>(forward<T>(value));
    }
    
    template<typename T, typename U = remove_reference_t<T>>
    constexpr auto operator=(T&& value) -> variant&
    {
        this->emplace<U>(forward<T>(value));
        return *this;
    }

    void reset()
    {
        if (this->_hold_index != unsuported_type_id)
        {
            private_variant::destroyer<
                0, T1, T2, T3, T4,T5, T6, T7, T8
                >::destroy(this->_hold_index, this->_storage.data);
                
            this->_hold_index = unsuported_type_id;
        }
    }
    
    
    // Query 
    
    constexpr auto index() const -> index_type { return this->_hold_index; }
    constexpr auto valueless_by_exception() const -> bool
    {
        return this->_hold_index == unsuported_type_id;
    }
    
    template<typename T>
    constexpr auto holds_alternative() -> bool
    {
        static_assert(is_suported_v<T>, "T is not a alternative to this variant");
        return this->_hold_index == type_id_lookup<T>::value;
    }

    
    // Access
    
    template <typename T>
    constexpr auto get() -> T&
    {
        static_assert(is_suported_v<T>, "T is not a alternative to this variant");
        constexpr index_type idx = type_id_lookup<T>::value;
        
        // Accept UB instead of exceptions
        return *reinterpret_cast<T*>(&this->_storage.data);
    }

    template <typename T>
    constexpr auto get() const -> const T&
    {
        static_assert(is_suported_v<T>, "T is not a alternative to this variant");
        constexpr index_type idx = type_id_lookup<T>::value;
        
        // Accept UB instead of exceptions
        return *reinterpret_cast<const T*>(&this->_storage.data);
    }
    
    private:
    index_type _hold_index = unsuported_type_id;
    storage_type _storage{};
};

template <typename T, typename... Ts>
constexpr auto get_if(variant<Ts...>* v) -> T* 
{
    using variant_t = variant<Ts...>;
    constexpr typename variant_t::index_type idx = variant_t:: template type_id_lookup<T>::value;
    
    if (!v) return nullptr;
    if (v->index() != idx) return nullptr;

    return reinterpret_cast<T*>(&v-> template get<T>());
}

template <typename T, typename... Ts>
constexpr auto get_if(const variant<Ts...>* v) -> const T*
{
    return const_cast<const T*>(get_if<T, Ts...>(const_cast<variant<Ts...>*>(v)));
}

}

#endif
