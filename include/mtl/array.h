///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2025 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file array.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 01-02-2025
///
///-----------------------------------------------------------------------------

#ifndef MTL_ARRAY_H
#define MTL_ARRAY_H

#include <cstdint>
#include <cstddef>

namespace mtl
{
template<typename T, std::size_t N> class array
{
    public:
    static_assert(N > 0, "array<T, 0> is ill-formed");

    using value_type             = T;
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using pointer                = value_type*;
    using const_pointer          = const value_type*;
    using iterator               = pointer;
    using const_iterator         = const_pointer;
    
    value_type _elems[N]; // aggregate storage

    /// @brief Access operator.
    constexpr auto operator[](size_type i) -> reference { return this->_elems[i]; }
    /// @brief Access operator.
    constexpr auto operator[](size_type i) const -> const_reference { return this->_elems[i]; }

    /// @brief First element of the array.
    constexpr auto front() -> reference { return this->_elems[0]; }
    /// @brief First element of the array.
    constexpr auto front() const -> const_reference { return this->_elems[0]; }
    
    /// @brief Last element of the array.
    constexpr auto back() -> reference { return this->_elems[N - 1]; }
    /// @brief Last element of the array.
    constexpr auto back() const -> const_reference { return this->_elems[N - 1]; }

    /// @brief Raw data.
    constexpr auto data() -> pointer { return this->_elems; }
    /// @brief Raw data.
    constexpr auto data() const -> const_pointer { return this->_elems; }
    
    /// @brief Iterator to begin of the array.
    constexpr auto begin() -> iterator { return this->_elems; }
    /// @brief Iterator to begin of the array.
    constexpr auto begin() const -> const_iterator { return this->_elems; }

    /// @brief Iterator to end of the array.
    constexpr auto end() -> iterator { return this->_elems + N; }
    /// @brief Iterator to end of the array.
    constexpr auto end() const -> const_iterator { return this->_elems + N; }

    /// @brief Gets the capacity.
    static constexpr auto size() -> size_type { return N; }

    /// @brief Fills the array with `value`
    constexpr void fill(const value_type& value)
    {
        for (auto& e : this->_elems) { e = value; }
    }
};
} // namespace util

#endif
