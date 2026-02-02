///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2025 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file ringbuf.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 29-07-2025
///
///-----------------------------------------------------------------------------

#ifndef MTL_RINGBUF_H
#define MTL_RINGBUF_H

#include <cstddef>

#include "algorithm.h"

namespace mtl
{
template <typename T, size_t SIZE>
class ring_buffer
{
    public:
    using size_type        = size_t;
    using reference        = T&;
    using const_reference  = const T&;
    using iterator         = T*;
    using const_iterator   = const T*;
    
    auto write(const_iterator data, size_type n) -> size_type
    {
        n = min(n, this->get_free());
        if (n == 0) { return n; }

        const size_type first_chunk = min(n, SIZE - this->_end);
        
        copy_n(data, first_chunk * sizeof(T), this->_arena + this->_end);
        this->_end = (this->_end + first_chunk) % SIZE;

        if (first_chunk < n)
        {
            const size_type second_chunk = n - first_chunk;

            copy_n(data + first_chunk, second_chunk * sizeof(T), this->_arena + this->_end);
            this->_end = (this->_end + second_chunk) % SIZE;
        }

        if (this->_begin == this->_end)
        {
            this->_wrap = true;
        }

        return n;
    }

    auto read(iterator dest, size_type n) -> size_type
    {
        n = min(n, get_occupied());
        if (n == 0) { return n; }

        if (this->_wrap)
        {
            this->_wrap = false;
        }

        const size_type first_chunk = min(n, SIZE - this->_begin);
        
        copy_n(this->_arena + this->_begin, first_chunk * sizeof(T), dest);
        this->_begin = (this->_begin + first_chunk) % SIZE;

        if (first_chunk < n)
        {
            const size_type second_chunk = n - first_chunk;
            copy_n(this->_arena + this->_begin, second_chunk * sizeof(T), dest + first_chunk);

            this->_begin = (this->_begin + second_chunk) % SIZE;
        }
        return n;
    }

    auto get_occupied() const -> size_type
    {
        if (this->_end == this->_begin)
        {
            return this->_wrap ? SIZE : 0u;
        }

        if (this->_end > this->_begin)
        {
            return this->_end - this->_begin;
        }

        return SIZE + this->_end - this->_begin;
    }

    auto get_free() const -> size_type { return SIZE - this->get_occupied(); }
    
    private:
    T _arena[SIZE]{};

    size_type _begin = 0;
    size_type _end   = 0;
    bool   _wrap     = false;
};
}

#endif
