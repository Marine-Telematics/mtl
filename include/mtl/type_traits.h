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

namespace mtl
{
template<typename T> struct remove_reference      { using type = T; };
template<typename T> struct remove_reference<T&>  { using type = T; };
template<typename T> struct remove_reference<T&&> { using type = T; };

template<typename T> using remove_reference_t = typename remove_reference<T>::type;

template <typename T> struct add_rvalue_reference { using type = T&&; };
template <typename T> struct add_rvalue_reference<T&> { using type = T&; };

template <typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;
}

#endif
