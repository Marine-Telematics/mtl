///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2026 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file aligned_storage.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 09-02-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_ALIGNED_STORAGE_H
#define MTL_ALIGNED_STORAGE_H

#include <cstddef>
#include <cstdint>

namespace mtl
{
/// @brief Creates a buffer of type `B` using the size and alignment of `T`.
template <typename T, typename B = unsigned char> class aligned_storage
{
    public:
    using pointer       = T *;
    using const_pointer = const T *;

    auto data() -> pointer { return reinterpret_cast<pointer>(this->_t_buff); }
    auto data() const -> const_pointer { return reinterpret_cast<const_pointer>(this->_t_buff); }

    // std::aligned_storage_t<sizeof(T), alignof(T)> t_buff;
    alignas(T) B _t_buff[sizeof(T)];
};
} // namespace mtl

#endif
