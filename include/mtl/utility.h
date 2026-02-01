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
template<typename T>
constexpr auto forward(remove_reference_t<T>& t) -> T&&
{
    return static_cast<T&&>(t);
}

template<typename T>
constexpr auto move(T&& t) -> remove_reference_t<T>&&
{
    return static_cast<remove_reference_t<T>&&>(t);
}

template <typename T> auto declval() -> add_rvalue_reference_t<T>;
}

#endif
