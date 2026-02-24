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
/// @brief Checks if `val` is the same value as one of many `opts`.
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
}

#endif
