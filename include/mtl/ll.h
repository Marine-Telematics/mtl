///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2025 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file ll.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 02-02-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_LL_H
#define MTL_LL_H

namespace mtl
{
class logic_level
{
    public:
    enum value
    {
        low      = 0,
        high     = 1,
        tristate = 3,
    };

    constexpr auto operator==(const logic_level &other) const -> bool
    {
        return this->_val == other._val;
    };

    constexpr auto operator==(const logic_level &&other) const -> bool
    {
        return this->_val == other._val;
    };

    constexpr auto operator==(const value other) const -> bool
    {
        return this->_val == other;
    };

    constexpr auto operator=(const value other) -> logic_level&
    {
        this->_val = other;
        return *this;
    };

    constexpr operator bool() const { return this->_val == high; };

    constexpr logic_level(const bool state) : _val(state ? high : low) {};
    constexpr logic_level(const value value) : _val(value) {};
    constexpr logic_level() = default;
    
    private:
    value _val = tristate;
};
}

#endif
