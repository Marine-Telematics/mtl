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

#include <new>
#include <utility>

#include "aligned_storage.h"

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
        if (!constructed)
        {
            new (buffer.data()) value_t(std::forward<Args>(args)...);
            constructed = true;
        }

        return instance();
    }

    static auto instance() -> reference { return *(buffer.data()); }

    static void destroy()
    {
        if (constructed)
        {
            instance().~value_t();
            constructed = false;
        }
    }

    singleton() = delete;

    private:
    inline static aligned_storage<value_t> buffer{};
    inline static bool constructed;
};
}

#endif
