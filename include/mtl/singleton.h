///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2025 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file singleton.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 31-01-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_SINGLETON_H
#define MTL_SINGLETON_H

#include "new.h"
#include "utility.h"

namespace mtl
{
template <typename T> class singleton
{
    public:
    using value_t   = T;
    using reference = T&;
    using pointer   = T*;

    template <typename... Args>
    static auto create(Args&&... args) -> reference
    {
        if (!_constructed)
        {
            new (_buffer) value_t(forward<Args>(args)...);
            _constructed = true;
        }

        return instance();
    }

    static auto instance() -> reference
    {
        return *static_cast<pointer>(static_cast<void*>(_buffer));
    }

    static void destroy()
    {
        if (_constructed)
        {
            instance().~value_t();
            _constructed = false;
        }
    }

    singleton() = delete;

    private:
    alignas(value_t) inline static unsigned char _buffer[sizeof(value_t)];
    inline static bool _constructed = false;
};
}

#endif
