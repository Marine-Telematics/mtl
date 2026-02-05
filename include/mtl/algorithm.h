///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2025 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file algorithm.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 01-02-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_ALGORITHM_H
#define MTL_ALGORITHM_H

namespace mtl
{
template<class Size, class InputIt = void *, class OutputIt = void *>
inline constexpr void copy_n(InputIt first, Size count, OutputIt result)
{
#ifdef __ICCARM__
    __aeabi_memcpy(result, first, count);
#else
    __builtin_memcpy(result, first, count);
#endif
}

template<typename T>
constexpr const T& clamp(const T& v, const T& lo, const T& hi)
{
    // Same precondition as the standard: !(hi < lo) must be true
    return (v < lo) ? lo : (hi < v) ? hi : v;
}

template<class T>
inline constexpr auto max(const T& a, const T& b) -> const T& { return (b < a) ? a : b; }

template<class T, class Compare>
inline constexpr auto max(const T& a, const T& b, Compare comp) -> const T&
{
    return (comp(b, a)) ? a : b;
}

template<class T>
inline constexpr auto min(const T& a, const T& b) -> const T&  { return (b < a) ? b : a; }

template<class T, class Compare>
inline constexpr auto min(const T& a, const T& b, Compare comp) -> const T&
{
    return (comp(b, a)) ? b : a;
}

template <typename T, typename... Opts>
inline constexpr auto oneof(T &&val, Opts &&...opts) -> bool
{
    return sizeof...(opts) == 0 ? false : (... || (val == opts));
}
}

#endif
