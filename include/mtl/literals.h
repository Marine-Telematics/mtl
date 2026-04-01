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

///////////////////////// TIME LITERALS ////////////////////////////////

namespace mtl::time_literals
{
namespace private_literals
{
struct base
{
    uint32_t _val;

    constexpr operator uint32_t() const { return _val; }
    constexpr base(uint32_t v) : _val(v) {}
};
}

struct hz;
struct ms;
struct s;

struct hz : private_literals::base
{
    constexpr auto period_ms() const -> ms;
    constexpr auto period_s() const -> s;
    using private_literals::base::base;
};

struct ms : private_literals::base
{
    constexpr auto frequency() const -> hz;
    constexpr operator s() const;
    using private_literals::base::base;
};

struct s : private_literals::base
{
    constexpr auto frequency() const -> hz;
    constexpr operator ms() const;
    using private_literals::base::base;
};

constexpr auto hz::period_ms() const -> ms { return ms(1000u / this->_val); }
constexpr auto hz::period_s() const -> s { return s(1u / this->_val); }

constexpr auto ms::frequency() const -> hz { return hz(1000u / this->_val); }
constexpr ms::operator s() const { return s(this->_val / 1000u); }

constexpr auto s::frequency() const -> hz { return hz(1u / this->_val); }
constexpr s::operator ms() const { return ms(this->_val * 1000u); }
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

///////////////////////// ELECTRIC LITERALS ////////////////////////////////

namespace mtl::electric_literals
{
namespace private_literals
{
template<typename T = float>
struct base
{
    using und_t = T;

    und_t _val;

    constexpr operator und_t() const { return _val; }
    constexpr base(und_t v) : _val(v) {}
};
}

struct V;
struct A;
struct W;  // TODO: Add W and mW, multiplication operators for V and A resulting in W and etc.

struct Ohms;

struct V : private_literals::base<>
{
    using private_literals::base<>::base;
};

struct A : private_literals::base<>
{
    using private_literals::base<>::base;
};

struct Ohms : private_literals::base<>
{
    using private_literals::base<>::base;
};
}

constexpr auto operator"" _V(unsigned long long v) -> mtl::electric_literals::V
{
    return static_cast<mtl::electric_literals::private_literals::base<>::und_t>(v);
}

constexpr auto operator"" _mV(unsigned long long v) -> mtl::electric_literals::V
{
    return static_cast<mtl::electric_literals::private_literals::base<>::und_t>(v) / 1'000.f;
}

constexpr auto operator"" _uV(unsigned long long v) -> mtl::electric_literals::V
{
    return static_cast<mtl::electric_literals::private_literals::base<>::und_t>(v) / 1'000'000.f;
}

constexpr auto operator"" _A(unsigned long long v) -> mtl::electric_literals::A
{
    return static_cast<mtl::electric_literals::private_literals::base<>::und_t>(v);
}

constexpr auto operator"" _mA(unsigned long long v) -> mtl::electric_literals::A
{
    return static_cast<mtl::electric_literals::private_literals::base<>::und_t>(v) / 1'000.f;
}

constexpr auto operator"" _uA(unsigned long long v) -> mtl::electric_literals::A
{
    return static_cast<mtl::electric_literals::private_literals::base<>::und_t>(v) / 1'000'000.f;
}

constexpr auto operator"" _kOhms(unsigned long long v) -> mtl::electric_literals::Ohms
{
    return static_cast<mtl::electric_literals::private_literals::base<>::und_t>(v) * 1000.f;
}

constexpr auto operator"" _Ohms(unsigned long long v) -> mtl::electric_literals::Ohms
{
    return static_cast<mtl::electric_literals::private_literals::base<>::und_t>(v);
}

constexpr auto operator"" _mOhms(unsigned long long v) -> mtl::electric_literals::Ohms
{
    return static_cast<mtl::electric_literals::private_literals::base<>::und_t>(v) / 1000.f;
}

#endif
