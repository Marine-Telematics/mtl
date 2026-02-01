///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2025 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file bitset.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 01-02-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_BITSET_H
#define MTL_BITSET_H

#include <cstdint>
#include <cstddef>

#include "type_traits.h"

namespace mtl
{
template<size_t N = 0u> class bitset
{
    public:
    using value_type =
        conditional_t<N <= 8u,  uint8_t,
        conditional_t<N <= 16u, uint16_t,
        conditional_t<N <= 32u, uint32_t,
                                uint64_t>>>;;

    static_assert(N > 0,   "bitset<N>: N must be > 0");
    static_assert(N <= 64, "bitset<N>: N > 64u not supported");

    constexpr bitset(const char* bitstring)
    {
        size_t bit_index = 0;

        for (size_t i = 0u; bitstring[i] != '\0'; ++i)
        {
            const char c = bitstring[i];

            if (c == '_')
            {
                continue; // separator
            }
            else if (c == '0' || c == '1')
            {
                if (c == '1')
                {
                    this->_val |= static_cast<uint8_t>(
                        1u << (N - 1u - bit_index)
                    );
                }

                ++bit_index;
            }
        }
    }
    
    /// @brief Gets the equivalent numbers of this bitset.
    constexpr auto value() const -> value_type { return this->_val; }
    
    // proxy for bit assign operations `bitset[N] = true;`
    struct bit_ref
    {
        value_type& _word;
        value_type  _mask;

        constexpr bit_ref(value_type &w, value_type m) : _word(w), _mask(m) {}
        
        constexpr auto operator=(const bit_ref& other) -> bit_ref&
        {
            return *this = static_cast<bool>(other);
        }

        constexpr auto operator=(const bool value) -> bit_ref&
        {
            if (value) this->_word |= this->_mask;
            else this->_word &= ~this->_mask;

            return *this;
        }

        constexpr operator bool() const { return (this->_word & this->_mask) != 0u; }
    };
    
    /// @brief bit level proxy access, for assign operator.
    constexpr auto operator[](std::size_t i) -> bit_ref
    {
        return bit_ref{this->_val, static_cast<value_type>(1u << i)};
    }
    
    /// @brief Gets the value of a single bit.
    constexpr auto operator[](size_t i) const -> bool
    {
        return (this->_val & (1u << i)) != 0u;
    }
    
    private:
    value_type _val = 0u;
};
}

#endif
