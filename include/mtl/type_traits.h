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
// integral_constant
template <typename T, T v>
struct integral_constant { static constexpr T value = v; };

using true_type  = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

// *****************************************
// remove_reference
template<typename T> struct remove_reference      { using type = T; };
template<typename T> struct remove_reference<T&>  { using type = T; };
template<typename T> struct remove_reference<T&&> { using type = T; };

template<typename T> using remove_reference_t = typename remove_reference<T>::type;

// *****************************************
// remove_cv
template<class T> struct remove_cv { typedef T type; };
template<class T> struct remove_cv<const T> { typedef T type; };
template<class T> struct remove_cv<volatile T> { typedef T type; };
template<class T> struct remove_cv<const volatile T> { typedef T type; };

template<typename T> using remove_cv_t = typename remove_cv<T>::type;

// *****************************************
// remove_const 
template<class T> struct remove_const { typedef T type; };
template<class T> struct remove_const<const T> { typedef T type; };

template<typename T> using remove_const_t = typename remove_const<T>::type;
 
// *****************************************
// remove_volatile 
template<class T> struct remove_volatile { typedef T type; };
template<class T> struct remove_volatile<volatile T> { typedef T type; };

template<typename T> using remove_volatile_t = typename remove_volatile<T>::type;

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
// is_same
template<typename T, typename U> struct is_same : false_type {};
template<typename T> struct is_same<T, T> : true_type {};

template<typename T, typename U> inline constexpr bool is_same_v = is_same<T, U>::value;

// *****************************************
// is_void
template<class T>
struct is_void : is_same<void, remove_cv_t<T>> {};

template<typename T> inline constexpr bool is_void_v = is_void<T>::value;

// *****************************************
// is_standard_layout
template <class T>
struct is_standard_layout : public integral_constant<bool, __is_standard_layout(T)> {};

template <class T>
inline constexpr bool is_standard_layout_v = is_standard_layout<T>::value;

// *****************************************
// enable_if
template <bool B, typename T = void> struct enable_if {};
template <typename T> struct enable_if<true, T> { using type = T; };

template<bool B, class T = void >
using enable_if_t = typename enable_if<B,T>::type;

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
