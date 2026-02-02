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

#include "utility.h"
#include "new.h"

namespace mtl
{
struct none_type {};
[[maybe_unused]] inline static constexpr none_type none{};

template <typename T> class option
{
    public:
    using value_type             = T;
    using size_type              = std::size_t;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using pointer                = value_type*;
    using const_pointer          = const value_type*;
    
    /// Constructors
    constexpr option() : _has(false) {}
    constexpr option([[maybe_unused]] const none_type&) : _has(false) { }
    constexpr option([[maybe_unused]] none_type&&) : _has(false) { }

    constexpr option(const T& value) : _has(true) { new (&this->_storage) T(value); }
    constexpr option(T&& value) : _has(true) { new (&this->_storage) T(move(value)); }

    /// Destructor
    ~option() { this->reset(); }

    /// Copy
    option(const option& other) : _has(other._has)
    {
        if (this->_has)
        {
            new (&this->_storage) T(other.value());
        }
    }

    auto operator=(const option& other) -> reference
    {
        if (this == &other) { return *this; }

        this->reset();
        if (other._has)
        {
            new (&this->_storage) T(other.value());
            this->_has = true;
        }
        
        return *this;
    }

    /// Move
    option(option&& other) : _has(other._has)
    {
        if (this->_has)
        {
            new (&this->_storage) T(move(other.value()));
        }
        
        other.reset();
    }

    auto operator=(option&& other) -> reference
    {
        if (this == &other) { return *this; }

        this->reset();
        if (other._has)
        {
            new (&_storage) T(move(other.value()));
            this->_has = true;
            other.reset();
        }
        return *this;
    }

    /// State
    constexpr auto is_some() const -> bool { return this->_has; }
    constexpr auto is_none() const -> bool { return !this->_has; }
    constexpr operator bool() const { return this->is_some(); }

    /// Access
    auto unwrap() -> reference
    {
        assert(this->_has && "Called unwrap() on None");
        return this->value();
    }

    auto unwrap() const -> const_reference
    {
        assert(this->_has && "Called unwrap() on None");
        return this->value();
    }
    
    constexpr auto operator*() -> reference { return this->unwrap(); }
    constexpr auto operator*() const -> const_reference { return this->unwrap(); }
    constexpr auto operator->() -> pointer { return &this->unwrap(); }
    constexpr auto operator->() const -> const_pointer{ return &this->unwrap()(); }

    auto as_ptr() -> pointer { return this->_has ? &this->value() : nullptr; }
    auto as_ptr() const -> const_pointer { return this->_has ? &this->value() : nullptr; }
    
    template <typename F>
    auto map(F&& f) const -> option<decltype(f(declval<T>()))>
    {
        if (this->_has) return option<decltype(f(declval<T>()))>(f(this->value()));
        return {};
    }

    template <typename U>
    auto unwrap_or(U&& default_value) const -> value_type
    {
        return this->_has ? this->value() : static_cast<T>(forward<U>(default_value));
    }

    template <typename F>
    auto unwrap_or_else(F&& f) const -> value_type { return this->_has ? this->value() : f(); }

    void reset()
    {
        if (this->_has)
        {
            this->value().~T();
            this->_has = false;
        }
    }

    private:
    auto value() -> reference { return *reinterpret_cast<pointer>(&_storage); }
    auto value() const -> const_reference { return *reinterpret_cast<const_pointer>(&_storage); }

    bool _has;
    alignas(T) unsigned char _storage[sizeof(T)];
};
}

#endif
