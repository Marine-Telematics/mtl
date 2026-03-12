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

#include <span>
#include <array>
#include <cstdint>
#include <cstddef>
#include <utility>

namespace mtl::i2c
{
using addr_type = uint8_t;
using data_type = uint8_t;
using size_type = size_t;

enum class mode : uint8_t
{
    master = 0,
    slave  = 1,
};

enum class speed : uint8_t
{
    standard  = 0, // 100 kHz
    fast      = 1, // 400 kHz
    fast_plus = 2, // 1 MHz
    high      = 3, // 3.4 MHz
};

inline static constexpr auto message_use_span_flag = std::numeric_limits<size_type>::max();

template<size_type SZ = message_use_span_flag>
struct message;

template<> struct message<message_use_span_flag>
{
    addr_type _addr;
    std::span<data_type> _data;
};

template<size_type SZ> struct message
{
    addr_type _addr;
    std::array<data_type, SZ> _data{};

    constexpr operator message<>() { return {_addr, _data}; }
    constexpr operator message<>() const { return {_addr, _data}; }
};
}

#endif
