///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2025 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file utility.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 01-02-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_UTILITY_H
#define MTL_UTILITY_H

#include "type_traits.h"

namespace mtl
{
/// @brief Similar to std::forward<T>()
template<typename T>
constexpr auto forward(remove_reference_t<T>& t) -> T&&
{
    return static_cast<T&&>(t);
}

/// @brief Similar to std::forward<T>()
template <typename T>
constexpr auto forward(remove_reference_t<T>&& t) -> T&&
{
    return static_cast<T&&>(t);
}

/// @brief Similar to std::move<T>()
template<typename T>
constexpr auto move(T&& t) -> remove_reference_t<T>&&
{
    return static_cast<remove_reference_t<T>&&>(t);
}

/// @brief Similar to std::declval()
template <typename T> auto declval() -> add_rvalue_reference_t<T>;

/// @brief Similar to std::to_underlying()
template<typename E>
constexpr auto to_underlying(E e)
{
    static_assert(__is_enum(E), "to_underlying requires an enum type");
    return static_cast<__underlying_type(E)>(e);
}

template <typename T1, typename T2>
struct pair
{
    T1 _first;
    T2 _second;

    constexpr pair() = default;

    constexpr pair(const T1& a, const T2& b)
        : _first(a), _second(b) {}

    template <typename U1, typename U2>
    constexpr pair(U1&& a, U2&& b)
        : _first(static_cast<U1&&>(a)), _second(static_cast<U2&&>(b)) {}
};

template<typename T1, typename T2>
constexpr auto make_pair(T1 &&t1, T2 &&t2) -> pair<remove_reference_t<T1>, remove_reference_t<T2>>
{
    return pair(move(t1), move(t2));
}
}

#endif
