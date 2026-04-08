///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2025 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file utility.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 01-02-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_UTILITY_H
#define MTL_UTILITY_H

#include <cstdint>
#include <type_traits>

namespace mtl
{
/// @brief Runs a callable object at the end of the scope.
/// @note This class is menat to be used by `mtl::defer`
template<typename Fn>
struct final_action
{
    static_assert(std::is_invocable_v<Fn>, "Fn must be invocable");

    Fn f;
    ~final_action() { f(); }
};

/// @brief Runs a callable object at the end of the scope of the calle.
///
/// @code
/// static mutex<int> _mutex_obj;
/// void increment_mutex_val()
/// {
///     _mutex_obj.lock();
///     auto _ = mtl::defer([&] { _mutex_obj.unlock(); })
/// 
///     return _mutex_obj.with_lock([](int &val) { return ++val; });
/// }
/// @endcode
template<typename Fn, typename Ret = final_action<Fn>>
[[nodiscard]] auto defer(Fn &&f) -> Ret
{
    return {f};
}

/// @brief Converts a value into a BCD representation, useful for displays.
inline auto to_bcd(const uint8_t value) -> uint8_t
{
    const uint8_t tens  = value / 10u;
    const uint8_t units = value % 10u;
    return (uint8_t)((tens << 4u) | units);
}

/// @brief Converts a value into a BCD representation, useful for displays.
inline auto to_bcd(const uint16_t value) -> uint16_t
{
    const uint16_t thousands = value / 1000u;
    const uint16_t hundreds  = (value / 100u) % 10u;
    const uint16_t tens      = (value / 10u) % 10u;
    const uint16_t units     = value % 10u;

    return (uint16_t)((thousands << 12u) | (hundreds << 8u) | (tens << 4u) | units);
}
}

#endif
