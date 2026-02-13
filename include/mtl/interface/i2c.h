///-----------------------------------------------------------------------------
/// MarineTelematics Template Library (Interface) - (c) 2026 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file i2c.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 09-02-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_INTERFACE_I2C_H
#define MTL_INTERFACE_I2C_H

#include <cstdint>
#include <cstddef>

#include "../array.h"

namespace mtl::i2c
{
using addr_type = uint8_t;
using data_type = uint8_t;
using size_type = size_t;

template<size_type SZ> class message
{
    addr_type _addr;
    array<data_type, SZ> _data{};
};
}

#endif
