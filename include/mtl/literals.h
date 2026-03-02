///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2026 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file literals.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 01-03-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_LITERALS_H
#define MTL_LITERALS_H

#include <cstdint>
#include <type_traits>

namespace mtl::time_literals
{
namespace private_time_literals
{
struct base
{
    uint32_t _val;

    constexpr operator uint32_t() { return _val; }
    constexpr explicit base(uint32_t v) : _val(v) {}
};
}

struct hz;
struct ms;
struct s;

struct hz : private_time_literals::base
{
    constexpr operator ms();
    constexpr operator s();
    using private_time_literals::base::base;
};

struct ms : private_time_literals::base
{
    constexpr operator hz();
    constexpr operator s();
    using private_time_literals::base::base;
};

struct s : private_time_literals::base
{
    constexpr operator hz();
    constexpr operator ms();
    using private_time_literals::base::base;
};

constexpr hz::operator ms() { return ms(1000u / this->_val); }
constexpr hz::operator s() { return ms(1u / this->_val); }

constexpr ms::operator hz() { return hz(1000u / this->_val); }
constexpr ms::operator s() { return s(this->_val / 1000u); }

constexpr s::operator hz() { return hz(1u / this->_val); }
constexpr s::operator ms() { return ms(this->_val * 1000u); }
}

constexpr mtl::time_literals::hz operator"" _hz(unsigned long long v)
{
    return mtl::time_literals::hz(static_cast<uint32_t>(v));
}

constexpr mtl::time_literals::ms operator"" _ms(unsigned long long v)
{
    return mtl::time_literals::ms(static_cast<uint32_t>(v));
}

constexpr mtl::time_literals::s operator"" _s(unsigned long long v)
{
    return mtl::time_literals::s(static_cast<uint32_t>(v));
}

#endif
