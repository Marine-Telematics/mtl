///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2025 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file math_constants.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 02-02-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_MATH_CONSTANTS_H
#define MTL_MATH_CONSTANTS_H

namespace mtl
{
template <typename T = float>
struct math_constants
{
    static constexpr T pi               = 3.14159265358979;
    static constexpr T pi_reciprocal    = 0.31830988618379;
    static constexpr T pi_squared       = 9.86960440108936;
    static constexpr T e                = 2.71828182845905;
    static constexpr T e_reciprocal     = 0.36787944117144;
    static constexpr T e_squared        = 7.38905609893065;
    static constexpr T root2            = 1.41421356237310;
    static constexpr T root2_reciprocal = 0.70710678118655;
    static constexpr T euler            = 0.57721566490153;
    static constexpr T golden_ratio     = 1.61803398874989;
};
}

#endif
