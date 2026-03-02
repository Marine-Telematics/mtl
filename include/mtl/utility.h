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

#include <type_traits>

namespace mtl
{
/// @brief Runs a callable object at the end of the scope.
/// @note This class is menat to be used by `mtl::defer`
template<typename Fn>
    requires std::is_invocable_v<Fn>
struct final_action
{
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
}

#endif
