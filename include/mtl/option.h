///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2025 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file option.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 01-02-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_OPTION_H
#define MTL_OPTION_H

#include <cstddef>
#include <cassert>
#include <optional>

namespace mtl
{
[[maybe_unused]] inline static constexpr std::nullopt_t none = std::nullopt;

template <class T>
class option : public std::optional<T>
{
    public:
    using std::optional<T>::optional;

    constexpr auto is_some() -> bool { return this->has_value(); }
    constexpr auto is_none() -> bool { return !(this->is_some()); }

    constexpr auto some() -> T& { return this->value(); }
};

template<class T, class... Args>
constexpr auto make_optional(Args&&... args) -> option<T>
{
    return std::make_optional<T>(forward<Args>(args)...);
}
}

#endif
