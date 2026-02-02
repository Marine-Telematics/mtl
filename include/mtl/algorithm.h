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
    if (count > 0u)
    {
        *result = *first;
        ++result;
        for (Size i = 1u; i != count; ++i, ++result) *result = *++first;
    }
}

template<typename T>
constexpr const T& clamp(const T& v, const T& lo, const T& hi)
{
    // Same precondition as the standard: !(hi < lo) must be true
    return (v < lo) ? lo : (hi < v) ? hi : v;
}

template<class T>
const T& max(const T& a, const T& b) { return (b < a) ? a : b; }

template<class T, class Compare>
const T& max(const T& a, const T& b, Compare comp) { return (comp(b, a)) ? a : b; }

template<class T>
const T& min(const T& a, const T& b) { return (b < a) ? b : a; }

template<class T, class Compare>
const T& min(const T& a, const T& b, Compare comp) { return (comp(b, a)) ? b : a; }
}

#endif
