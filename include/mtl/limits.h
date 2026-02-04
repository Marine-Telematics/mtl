///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2025 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file limits.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 03-02-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_LIMITS_H
#define MTL_LIMITS_H

#include <cstdint>

namespace mtl
{
template <typename T>
struct numeric_limits
{
    static constexpr bool is_specialized = false;

    static constexpr T min() noexcept { return T{}; }
    static constexpr T max() noexcept { return T{}; }
    static constexpr T lowest() noexcept { return T{}; }

    static constexpr bool is_signed  = false;
    static constexpr bool is_integer = false;
    static constexpr int digits      = 0;
    static constexpr int digits10    = 0;
};

#define NUMERIC_LIMITS_SIGNED(type, bits)                                           \
    template <>                                                                     \
    struct numeric_limits<type>                                                     \
    {                                                                               \
        static constexpr bool is_specialized = true;                                \
        static constexpr bool is_signed  = true;                                    \
        static constexpr bool is_integer = true;                                    \
                                                                                    \
        static constexpr int digits   = bits - 1;                                   \
        static constexpr int digits10 = digits * 301 / 1000;                        \
                                                                                    \
        static constexpr auto min() -> type { return type(type(1) << (bits - 1)); } \
        static constexpr auto max() -> type { return type(~min()); }                \
        static constexpr auto lowest() -> type  { return min(); }                   \
    };
    
#define NUMERIC_LIMITS_UNSIGNED(type, bits)                            \
    template <>                                                        \
    struct numeric_limits<type>                                        \
    {                                                                  \
        static constexpr bool is_specialized = true;                   \
        static constexpr bool is_signed  = false;                      \
        static constexpr bool is_integer = true;                       \
                                                                       \
        static constexpr int digits   = bits;                          \
        static constexpr int digits10 = digits * 301 / 1000;           \
                                                                       \
        static constexpr auto min() -> type { return type(0); }        \
        static constexpr auto max() -> type { return type(~type(0)); } \
        static constexpr auto lowest() -> type  { return min(); }      \
    };

NUMERIC_LIMITS_SIGNED(int8_t,   8);
NUMERIC_LIMITS_UNSIGNED(uint8_t, 8);

NUMERIC_LIMITS_SIGNED(int16_t,   16);
NUMERIC_LIMITS_UNSIGNED(uint16_t, 16);

NUMERIC_LIMITS_SIGNED(int32_t,   32);
NUMERIC_LIMITS_UNSIGNED(uint32_t, 32);

NUMERIC_LIMITS_SIGNED(int64_t,   64);
NUMERIC_LIMITS_UNSIGNED(uint64_t, 64);

template <>
struct numeric_limits<float>
{
    static constexpr bool is_specialized = true;
    static constexpr bool is_signed  = true;
    static constexpr bool is_integer = false;

    static constexpr int digits   = 24;
    static constexpr int digits10 = 6;

    static constexpr float min() noexcept
    {
        return 1.17549435e-38f; // FLT_MIN
    }

    static constexpr float max() noexcept
    {
        return 3.40282347e+38f; // FLT_MAX
    }

    static constexpr float lowest() noexcept
    {
        return -max();
    }

    static constexpr float epsilon() noexcept
    {
        return 1.19209290e-7f; // FLT_EPSILON
    }

    static constexpr float infinity() noexcept
    {
        return __builtin_huge_valf();
    }
};

template <>
struct numeric_limits<double>
{
    static constexpr bool is_specialized = true;
    static constexpr bool is_signed  = true;
    static constexpr bool is_integer = false;

    static constexpr int digits   = 53;
    static constexpr int digits10 = 15;

    static constexpr double min() noexcept
    {
        return 2.2250738585072014e-308;
    }

    static constexpr double max() noexcept
    {
        return 1.7976931348623158e+308;
    }

    static constexpr double lowest() noexcept
    {
        return -max();
    }

    static constexpr double epsilon() noexcept
    {
        return 2.2204460492503131e-16;
    }

    static constexpr double infinity() noexcept
    {
        return __builtin_huge_val();
    }
};
}

#endif
