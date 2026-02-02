///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2025 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file queue.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 29-07-2025
///
///-----------------------------------------------------------------------------

#ifndef MTL_QUEUE_H
#define MTL_QUEUE_H

#include <cstddef>

#include "option.h"
#include "ringbuf.h"

namespace mtl
{
template <typename T, size_t LEN> class queue
{
    public:
    using storage_type    = ring_buffer<T, LEN>;
    using reference       = typename storage_type::reference;
    using const_reference = typename storage_type::const_reference;
    
    auto is_empty() const -> bool { return this->_ringbuffer.get_occupied() == 0u; }
    auto is_full() const -> bool { return this->_ringbuffer.get_free() == 0u; }

    auto enqueue(const_reference data) -> bool
    {
        if (this->_ringbuffer.get_free() < 1u)
        {
            return false;
        }

        return this->_ringbuffer.write(&data, 1u) == 1u;
    };

    auto dequeue(reference data) -> bool
    {
        if (this->_ringbuffer.get_occupied() < 1u)
        {
            return false;
        }

        return this->_ringbuffer.read(&data, 1u) == 1u;
    }

    auto dequeue() -> option<T>
    {
        if (T val; this->dequeue(val))
        {
            return move(val);
        }

        return none;
    }
    
    private:
    storage_type _ringbuffer;
};
} // namespace util

#endif
