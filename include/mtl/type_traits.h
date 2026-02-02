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
// *****************************************
// remove_reference
template<typename T> struct remove_reference      { using type = T; };
template<typename T> struct remove_reference<T&>  { using type = T; };
template<typename T> struct remove_reference<T&&> { using type = T; };

template<typename T> using remove_reference_t = typename remove_reference<T>::type;

// *****************************************
// add_rvalue_reference
template <typename T> struct add_rvalue_reference { using type = T&&; };
template <typename T> struct add_rvalue_reference<T&> { using type = T&; };

template <typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

// *****************************************
// conditional
template<bool B, class T, class F> struct conditional { using type = T; };
template<class T, class F> struct conditional<false, T, F> { using type = F; };

template<bool B, class T, class F > using conditional_t = typename conditional<B,T,F>::type;

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
}

#endif
