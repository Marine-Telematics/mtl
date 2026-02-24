///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2025 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file type_traits.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 31-01-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_TYPE_TRAITS_H
#define MTL_TYPE_TRAITS_H

#include <cstddef>

namespace mtl
{
// *****************************************
// has_const_iterator
template <typename T> class has_const_iterator
{
    template <typename C> static auto test(typename C::const_iterator *) -> char;
    template <typename C> static auto test(...) -> int;

    public:
    static constexpr bool value = sizeof(test<T>(nullptr)) == sizeof(char);
};

template <typename T> using has_const_iterator_v = typename has_const_iterator<T>::value;

// *****************************************
// alignment_of
template <typename T> struct alignment_of : integral_constant<size_t, alignof(T)> {};

template <typename T> inline constexpr size_t alignment_of_v = alignment_of<T>::value;
}

#endif
