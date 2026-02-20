///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2025 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file math.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 02-02-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_MATH_H
#define MTL_MATH_H

#include <cmath>

namespace mtl
{
inline static constexpr auto abs(int x) -> int { return (x < 0) ? -x : x; }
inline static constexpr auto abs(long x) -> long { return (x < 0) ? -x : x; }
inline static constexpr auto abs(long long x) -> long long { return (x < 0) ? -x : x; }

inline static constexpr auto abs(float x) -> float { return (x < 0.f) ? -x : x; }
inline static constexpr auto abs(double x) -> double { return (x < 0.0) ? -x : x; }
inline static constexpr auto abs(long double x) -> long double { return (x < 0.0L) ? -x : x; }

inline static constexpr auto fabs(float x) -> float { return (x < 0.f) ? -x : x; }
inline static constexpr auto fabs(double x) -> double { return (x < 0.0) ? -x : x; }
inline static constexpr auto fabs(long double x) -> long double { return (x < 0.0L) ? -x : x; }

template<typename T>
constexpr auto copysign(T mag, T sgn) -> T { return __builtin_copysign(mag, sgn); }

template<typename T>
constexpr auto signbit(T arg) -> bool { return __builtin_copysign(1, arg) <  0; }

inline static auto exp(double x) -> double { return __builtin_exp(x); }
inline static auto exp(float x) -> float { return __builtin_expf(x); }

inline static auto tan(double x) -> double { return __builtin_tan(x); }
inline static auto tanf(float x) -> float { return __builtin_tanf(x); }
}

#endif
