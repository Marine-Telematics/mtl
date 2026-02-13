///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2025 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file hash.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 21-10-2025
///
/// FNV-1a hash function implementation.
/// https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
///
///-----------------------------------------------------------------------------

#ifndef MTL_HASH_H
#define MTL_HASH_H

#include <cstdint>
#include <cstddef>

#include "string_view.h"

namespace mtl
{
namespace detail_fnv1a
{
    /// @brief Computes the FNV-1a hash of a string.
    ///
    /// @tparam T Type of the hash value (e.g., std::uint32_t, std::uint64_t).
    /// @tparam Basis The FNV offset basis.
    /// @tparam Prime The FNV prime.
    ///
    /// @param s The input string to hash.
    template <typename T, T Basis, T Prime> constexpr T fnv1a(const mtl::string_view s)
    {
        T hash = Basis; // offset basis
        for (const char c : s)
        {
            // FNV-1a algorithm: XOR byte into the least significant byte of
            // hash then multiply by the FNV prime.
            hash = (hash ^ static_cast<uint8_t>(c)) * Prime;
        }

        return hash;
    }
}

/// @brief Computes the 32-bit FNV-1a hash of a string.
constexpr auto fnv1a_32(const mtl::string_view s) -> uint32_t
{
    return detail_fnv1a::fnv1a<uint32_t, 0x811c9dc5u, 0x01000193u>(s);
}

/// @brief Computes the 64-bit FNV-1a hash of a string.
constexpr auto fnv1a_64(const mtl::string_view s) -> uint64_t
{
    return detail_fnv1a::fnv1a<uint64_t, 0xcbf29ce484222325ull, 0x00000100000001b3ull>(s);
}
}

#endif
