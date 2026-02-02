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
}

#endif
