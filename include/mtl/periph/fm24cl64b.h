///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2026 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file array.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 09-02-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_FM24CL64B_H
#define MTL_FM24CL64B_H

#include <array>
#include <cstddef>
#include <cstdint>
#include <algorithm>

#include "../interface/i2c.h"

namespace mtl
{
struct fm24cl64b
{
    using address = uint16_t;

    static constexpr address START_ADDR = 0x0000u;
    static constexpr address END_ADDR   = 0x1fffu;

    struct device_select
    {
        const bool _a2, _a1, _a0;
        constexpr device_select(const i2c::addr_type bin)
            : _a2(bin & 0b100), _a1(bin & 0b010), _a0(bin & 0b001)
        {
        }
    };

    static constexpr i2c::addr_type BASE_ADDR = 0b1010000u;

    static constexpr auto get_addr(const device_select sel) -> i2c::addr_type
    {
        return BASE_ADDR | (sel._a2 ? 0b100 : 0) | (sel._a1 ? 0b010 : 0) | (sel._a0 ? 0b001 : 0);
    }
};

/// This interface provides a abstraction in the way the FM24C16B FRAM expects data.
/// The implementation is Bus agnostic, user shall provide write and read functions.
class fm24cl64b_impl : public fm24cl64b
{   
    public:
    fm24cl64b_impl(const device_select sel) : _i2c_addr(get_addr(sel)) {}

    /// Bus agnostic implementations:

    template<typename T, typename Fn>
    auto write(const address addr, const T &obj, Fn &&sender)
    {
        std::array<i2c::data_type, sizeof(T) + sizeof(address)> buffer{};

        buffer[0] = (addr >> 8u) & 0xffu;
        buffer[1] = addr & 0xffu;

        std::copy_n(&obj, sizeof(T), buffer.data() + sizeof(address));

        return sender(this->_i2c_addr, buffer.data(), buffer.size());
    }

    template<typename T, typename Fn>
    auto read(T &obj_out, Fn &&reader)
    {
        return reader(this->_i2c_addr, &obj_out, sizeof(T));
    }

    template<typename Fn>
    auto point_to_addr(const address addr, Fn &&sender)
    {
        std::array<i2c::data_type, sizeof(address)> buffer{};

        buffer[0] = (addr >> 8u) & 0xffu;
        buffer[1] = addr & 0xffu;

        return sender(this->_i2c_addr, buffer.data(), buffer.size());
    }

    private:
    const i2c::addr_type _i2c_addr;
};
}

#endif
