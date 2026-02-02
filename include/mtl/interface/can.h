///-----------------------------------------------------------------------------
/// MarineTelematics Template Library (Interface) - (c) 2025 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file can.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 01-02-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_INTERFACE_CAN_H
#define MTL_INTERFACE_CAN_H

#include <cstdint>
#include <cstddef>

#include "../array.h"
#include "../span.h"
#include "../algorithm.h"
#include "../ranges.h"

namespace mtl::can
{
using id_type   = uint32_t;
using data_type = uint8_t;
using size_type = size_t;


// special address description flags for the CAN_ID:

// EFF/SFF is set in the MSB
[[maybe_unused]] inline static constexpr id_type eff_flag = 0x80000000UL;
// remote transmission request
[[maybe_unused]] inline static constexpr id_type rtr_flag = 0x40000000UL;
// error message frame
[[maybe_unused]] inline static constexpr id_type err_flag = 0x20000000UL;

// valid bits in CAN ID for frame formats:

// standard frame format (SFF)
[[maybe_unused]] inline static constexpr id_type sff_mask = 0x000007FFUL;
// extended frame format (EFF)
[[maybe_unused]] inline static constexpr id_type eff_mask = 0x1FFFFFFFUL;
// omit EFF, RTR, ERR flags
[[maybe_unused]] inline static constexpr id_type err_mask = 0x1FFFFFFFUL;

enum class speed : uint8_t
{
    can125_kbps,
    can200_kbps,
    can250_kbps,
    can500_kbps,
};

// Data Length Code(DLC) is the standard term for CAN _data length.
inline static constexpr size_type max_dlc = 8u;

struct message
{
    id_type _identifier = 0x00;

    bool _extended = true;

    size_type                 _dlc = 0u;
    array<data_type, max_dlc> _data{};

    message() = default;

    message(const id_type id, const bool ext, const size_t len, const data_type *payload)
        : _identifier(id), _extended(ext), _dlc(len)
    {
        copy_n(payload, len, this->_data.data());
    }

    message(const id_type id, const bool ext, const span<const data_type> payload)
        : _identifier(id), _extended(ext), _dlc(payload.size())
    {
        ranges::copy(payload, this->_data);
    }
};
}; // namespace trait::can

#endif
