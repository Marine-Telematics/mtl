///-----------------------------------------------------------------------------
/// MarineTelematics Template Library               - (c) 2026 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file enum_ops.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 12-03-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_ENUM_OPS_H
#define MTL_ENUM_OPS_H

#include <cstdint>

#define MTL_ADD_ENUM_OPS(E)                                                             \
    constexpr E operator|(const E a, const E b)                                           \
    {                                                                                     \
        return static_cast<E>(static_cast<size_t>(a) | static_cast<size_t>(b));           \
    }                                                                                     \
    constexpr E operator&(const E a, const E b)                                           \
    {                                                                                     \
        return static_cast<E>(static_cast<size_t>(a) & static_cast<size_t>(b));           \
    }                                                                                     \
    constexpr E operator^(const E a, const E b)                                           \
    {                                                                                     \
        return static_cast<E>(static_cast<size_t>(a) ^ static_cast<size_t>(b));           \
    }                                                                                     \
    constexpr E  operator~(const E a) { return static_cast<E>(~static_cast<size_t>(a)); } \
    constexpr E &operator|=(E &a, E b) { return a = a | b; }                              \
    constexpr E &operator&=(E &a, E b) { return a = a & b; }                              \
    constexpr E &operator^=(E &a, E b) { return a = a ^ b; }

namespace mtl
{
template<typename E>
auto has_flag(const E e, E f) -> bool { return ((e & f) == f); }
}

#endif
