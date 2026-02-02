///-----------------------------------------------------------------------------
/// Butterworth Low Pass Filter - (c) 2025 marine telematics
///-----------------------------------------------------------------------------
///
/// @file butterworth_lpf.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com)
/// @date 19-08-2025
///
/// Butterworth low-pass filter, fourth order.
///
/// Starting from analogue prototype transfer functions, using Tustin (bilinear)
/// transform to arrive at digital approximation.
///
/// Butterworth filters are 'maximally flat' before cut-off frequency, i.e. in
/// passband.
///
/// Gain of any order Butterworth low-pass filter at cut-off frequency
/// is -3dB (1/sqrt(2)).
/// However, attenuation slope is n * (-20dB/dec), where n is the filter order.
///-----------------------------------------------------------------------------

#ifndef MTL_FILTER_BUTTERWORTH_LPF_H
#define MTL_FILTER_BUTTERWORTH_LPF_H

#include <cstddef>

#include "../algorithm.h"
#include "../array.h"
#include "../math.h"
#include "../math_constants.h"
#include "../type_traits.h"
#include "defs.h"

namespace mtl::filter
{
// Butterworth Low Pass Filter (LPF) class template
// Order: 1 to 4
template <order Order, typename T = float>
class butterworth_lpf
{
    static constexpr order ORDER = Order;

    static constexpr float PI = math_constants<T>::pi;

    T _wc = T{0}; // [rad/s]  Cut-off frequency
    T _t  = T{1}; // [s] Sample time, default to 1 second
    
    T _fc;
    T _fs;

    array<T, static_cast<size_t>(ORDER) + 1u> _num{};
    array<T, static_cast<size_t>(ORDER) + 1u> _den{};

    array<T, static_cast<size_t>(ORDER) + 1u> _u{};
    array<T, static_cast<size_t>(ORDER) + 1u> _y{};
    
    /// @brief Pre-warps the cut-off frequency for the Butterworth filter.
    ///
    /// This method adjusts the cut-off frequency to account for the non-linear
    /// frequency mapping introduced by the bilinear (Tustin) transform. It
    /// ensures that the analog cut-off frequency is correctly mapped to the
    /// digital domain.
    constexpr void pre_warp()
    {
        // Check that fc <= fs / 2 (Nyquist)
        const T fc = clamp<T>(this->_fc, T{0}, this->_fs / T{2});

        this->_t = T{1} / this->_fs;

        // Computes the pre-warped cut-off frequency (`_wc`) in rad/s.
        this->_wc = (T{2} / this->_t) * tanf(PI * fc / this->_fs);
    }

    public:
    /// @brief Retrieves the current output value of the filter.
    constexpr auto value() const -> T { return this->_y[0]; }

    /// @brief Resets the filter state to its initial condition.
    constexpr void reset()
    {
        this->_u.fill(0.f);
        this->_y.fill(0.f);
    }

    /// @brief Updates the filter state with a new input value and computes the
    /// output.
    constexpr auto update(const T val) -> T
    {
        // Shift samples
        for (size_t i = static_cast<size_t>(ORDER); i > 0; --i)
        {
            this->_u[i] = this->_u[i - 1];
            this->_y[i] = this->_y[i - 1];
        }

        // Set new input
        this->_u[0] = val;
        this->_y[0] = T{0};

        // This loop calculates the output value (`_y[0]`) of the filter by
        // applying the filter coefficients to the input (`_u`) and output
        // (`_y`) buffers.
        //
        // - The numerator coefficients (`_num`) are multiplied with the input
        // values to contribute to the output.
        // - The denominator coefficients (`_den`) are multiplied with the past
        // output values (for `i > 0`) and subtracted to account for feedback.
        //
        // The result is stored in `_y[0]`, representing the current filtered
        // output.
        for (size_t i = 0; i <= static_cast<size_t>(ORDER); ++i)
        {
            this->_y[0] += this->_num[i] * this->_u[i];

            if (i > 0)
            {
                this->_y[0] -= this->_den[i] * this->_y[i];
            }
        }

        this->_y[0] /= this->_den[0];
        return this->_y[0];
    }

    /// @brief Constructor for Butterworth Low Pass Filter
    ///
    /// @param fc Cut-off frequency in Hz
    /// @param fs Sampling frequency in Hz
    constexpr butterworth_lpf(T fc, T fs) : _fc(fc), _fs(fs)
    {
        this->pre_warp();
        this->reset();

        // Set filter numerator and denominator coefficients

        // Pre-warped cut-off frequency in seconds
        const float wc_t = this->_wc * this->_t;
        // Pre-warped cut-off frequency squared
        const float wc_tsq = wc_t * wc_t;
        // Pre-warped cut-off frequency cubed
        const float wc_tcu = wc_t * wc_tsq;
        // Pre-warped cut-off frequency to the fourth power
        const float wc_tfo = wc_tsq * wc_tsq;

        if constexpr (ORDER == order::first)
        {
            this->_num[0] = wc_t;
            this->_num[1] = wc_t;

            this->_den[0] = 2 + wc_t;
            this->_den[1] = -2 + wc_t;
        }
        else if constexpr (ORDER == order::second)
        {
            this->_num[0] = wc_tsq;
            this->_num[1] = 2 * wc_tsq;
            this->_num[2] = wc_tsq;

            this->_den[0] = 4 + 2.8284 * wc_t + wc_tsq;
            this->_den[1] = -8 + 2 * wc_tsq;
            this->_den[2] = 4 - 2.8284 * wc_t + wc_tsq;
        }
        else if constexpr (ORDER == order::third)
        {
            this->_num[0] = wc_tcu;
            this->_num[1] = 3 * wc_tcu;
            this->_num[2] = 3 * wc_tcu;
            this->_num[3] = wc_tcu;

            this->_den[0] = 8 + 8 * wc_t + 4 * wc_tsq + wc_tcu;
            this->_den[1] = -24 - 8 * wc_t + 4 * wc_tsq + 3 * wc_tcu;
            this->_den[2] = 24 - 8 * wc_t - 4 * wc_tsq + 3 * wc_tcu;
            this->_den[3] = -8 + 8 * wc_t - 4 * wc_tsq + wc_tcu;
        }
        else if constexpr (ORDER == order::fourth)
        {
            this->_num[0] = wc_tfo;
            this->_num[1] = 4 * wc_tfo;
            this->_num[2] = 6 * wc_tfo;
            this->_num[3] = 4 * wc_tfo;
            this->_num[4] = wc_tfo;

            constexpr float ALPHA = 2.6132;
            constexpr float BETA  = 3.41430612;

            this->_den[0] = 16 + 8 * ALPHA * wc_t + 4 * BETA * wc_tsq + 2 * ALPHA * wc_tcu + wc_tfo;

            this->_den[1] = -64 - 16 * ALPHA * wc_t + 4 * ALPHA * wc_tcu + 4 * wc_tfo;

            this->_den[2] = 96 - 8 * BETA * wc_tsq + 6 * wc_tfo;

            this->_den[3] = -64 + 16 * ALPHA * wc_t - 4 * ALPHA * wc_tcu + 4 * wc_tfo;

            this->_den[4] = 16 - 8 * ALPHA * wc_t + 4 * BETA * wc_tsq - 2 * ALPHA * wc_tcu + wc_tfo;
        }
    }
};
} // namespace filter

#endif
