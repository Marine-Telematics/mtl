///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2025 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file span.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 01-02-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_SPAN_H
#define MTL_SPAN_H

#include <cstddef>

namespace mtl
{
template<typename T> class span
{
    public:
    using element_type = T;
    using value_type   = T;
    using pointer      = T*;
    using reference    = T&;
    using size_type    = size_t;

    constexpr span() : _ptr(nullptr), _size(0u) {}
    constexpr span(pointer ptr, size_type count) : _ptr(ptr), _size(count) {}

    template<size_type N>
    constexpr span(T (&arr)[N]) : _ptr(arr), _size(N) {}
    
    template<typename A>
    constexpr span(A &arr) : _ptr(arr.data()), _size(arr.size()) {}

    constexpr pointer data() const { return this->_ptr; }
    constexpr size_type size() const { return this->_size; }
    constexpr bool empty() const { return this->_size == 0u; }

    constexpr reference operator[](size_type i) const
    {
        return this->_ptr[i]; // unchecked (by design)
    }

    constexpr pointer begin() const { return this->_ptr; }
    constexpr pointer end()   const { return this->_ptr + this->_size; }

    private:
    pointer   _ptr;
    size_type _size;
};
}

#endif
