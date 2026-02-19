///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2025 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file ranges.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 01-02-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_RANGES_H
#define MTL_RANGES_H

#include "algorithm.h"

namespace mtl::ranges
{
template<class InputR, class OutputR>
inline constexpr void copy(InputR &input, OutputR &result)
{
    copy_n(input.data(), input.size(), result.data());
}

template<class InputR, class T>
inline constexpr auto find(InputR &input, const T& value)
{
    return mtl::find(input.begin(), input.end(), value);
}

template<class InputR, class UnaryPred>
inline constexpr auto find_if(InputR &input, UnaryPred p)
{
    return mtl::find_if(input.begin(), input.end(), p);
}

template<class InputR, class UnaryPred>
inline constexpr auto find_if_not(InputR &input, UnaryPred p)
{
    return mtl::find_if_not(input.begin(), input.end(), p);
}
}

#endif
