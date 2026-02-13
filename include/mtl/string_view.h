///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2026 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file string_view.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 09-02-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_STRING_VIEW_H
#define MTL_STRING_VIEW_H

namespace mtl
{
namespace detail_string_view
{
    template <typename CharT>
    class basic_string_view
    {
        public:
        using char_type     = CharT;
        using pointer       = CharT*;
        using const_pointer = const CharT*;
        using size_type     = size_t;

        template <size_type N>
        constexpr basic_string_view(CharT (&a)[N])
            : _p(a), _sz(N - 1) {}

        constexpr auto operator[](const size_type n) const -> char_type
        {
            return n < _sz ? _p[n] : CharT{};
        }

        constexpr auto size() const -> size_type { return _sz; }

        constexpr auto begin() -> pointer { return this->_p; }
        constexpr auto end() -> pointer { return this->_p + this->_sz; }

        constexpr auto begin() const -> pointer { return this->_p; }
        constexpr auto end() const -> pointer { return this->_p + this->_sz; }

        private:
        pointer _p;
        size_type _sz;
    };
}

using string_view         = detail_string_view::basic_string_view<const char>;
using mutable_string_view = detail_string_view::basic_string_view<char>;
}

#endif
