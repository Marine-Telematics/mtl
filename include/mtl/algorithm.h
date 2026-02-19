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

template <typename T>
constexpr bool in_range(const T value, const T desired, const T diff)
{
    return (desired - diff < value && desired + diff > value);
};

template<class InputIt, class T>
inline constexpr auto find(InputIt first, InputIt last, const T& value) -> InputIt
{
    for (; first != last; ++first)
    {
        if (*first == value) { return first; }
    }
 
    return last;
}

template<class InputIt, class UnaryPred>
inline constexpr auto find_if(InputIt first, InputIt last, UnaryPred p) -> InputIt
{
    for (; first != last; ++first)
    {
        if (p(*first)) return first;
    }
 
    return last;
}

template<class InputIt, class UnaryPred>
inline constexpr auto find_if_not(InputIt first, InputIt last, UnaryPred q) -> InputIt
{
    for (; first != last; ++first)
    {
        if (!q(*first)) return first;
    }
 
    return last;
}
}

#endif
