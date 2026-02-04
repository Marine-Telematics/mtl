///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2025 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file expected.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 03-02-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_RESULT_H
#define MTL_RESULT_H

#include <cstddef>
#include <cassert>

#include "new.h"
#include "utility.h"
#include "variant.h"
#include "algorithm.h"
#include "largest.h"

namespace mtl
{
template<typename E>
struct err
{
    E _err;
    
    using reference       = E&;
    using const_reference = const E&;
    
    constexpr err(const E &e) : _err(e) {}
    constexpr err(E &&e) : _err(move(e)) {}
    
    constexpr auto get() -> reference { return this->_err; }
    constexpr auto get() const -> const_reference { return this->_err; }
    
    template<typename ...Args>
    static constexpr auto make(Args&&... args) { return E(forward<Args>(args)...); }
};

namespace private_result
{
template<typename T, typename E>
struct storage
{
    using size_type  = size_t;
    using align_type = size_t;
    
    static constexpr auto size() -> size_type { return mtl::largest_type<T, E>::size; }
    static constexpr auto align() -> align_type { return mtl::largest_alignment_v<T, E>; }
    
    alignas(align()) unsigned char _data[size()]{};
}; 
}
    
    
template <typename T, typename E> class result
{
    public:
    using value_type   = T;
    using error_type   = E;
    using size_type    = size_t;
    using storage_type = private_result::storage<T, E>;
    
    /// Constructors
    constexpr result() : _ok(true) { new (this->_storage._data) T(); };
    constexpr result(const err<E>& error) : _ok(false) { new (this->_storage._data) err<E>(error); }
    constexpr result(err<E>&& error) : _ok(false) { new (this->_storage._data) err<E>(error); }

    constexpr result(const T& value) : _ok(true) { new (this->_storage._data) T(value); }
    constexpr result(T&& value) : _ok(true) { new (this->_storage._data) T(move(value)); }

    /// Destructor
    ~result() { this->reset(); }

    /// Copy
    result(const result& other) : _ok(other._ok)
    {
        copy_n(&other._storage, sizeof(other._storage), &this->_storage);
        this->_ok = other._ok;
    }

    auto operator=(const result& other) -> result&
    {
        if (this == &other) { return *this; }

        this->reset();
        
        copy_n(&other._storage, sizeof(other._storage), &this->_storage);
        this->_ok = other._ok;
        
        return *this;
    }

    /// Move
    result(result&& other) : _ok(other._ok)
    {
        copy_n(&other._storage, sizeof(other._storage), &this->_storage);
        this->_ok = other._ok;
        
        other.reset();
    }

    auto operator=(result&& other) -> result&
    {
        if (this == &other) { return *this; }

        this->reset();

        copy_n(&other._storage, sizeof(other._storage), &this->_storage);
        this->_ok = other._ok;
        
        other.reset();
        
        return *this;
    }

    /// State
    
    constexpr auto is_ok() const -> bool { return this->_ok; }
    constexpr auto is_err() const -> bool { return !this->_ok; }
    constexpr operator bool() const { return this->is_ok(); }

    /// Access
    
    auto value() -> T& { return *reinterpret_cast<T*>(_storage._data); }
    auto value() const -> const T& { return *reinterpret_cast<const T*>(_storage._data); }
    
    auto error() -> E& { return reinterpret_cast<err<E>*>(_storage._data)->get(); }
    auto error() const -> const E&
    {
        return reinterpret_cast<const err<E>*>(_storage._data)->get();
    }
    
    auto unwrap() -> T&
    {
        assert(this->_ok && "Called unwrap() on err<E>");
        return this->value();
    }

    auto unwrap() const -> const T&
    {
        assert(this->_ok && "Called unwrap() on err<E>");
        return this->value();
    }
    
    constexpr auto operator*() -> T& { return this->unwrap(); }
    constexpr auto operator*() const -> const T& { return this->unwrap(); }
    constexpr auto operator->() -> T* { return &this->unwrap(); }
    constexpr auto operator->() const -> const T*{ return &this->unwrap(); }

    auto as_ptr() -> T* { return this->_ok ? &this->value() : nullptr; }
    auto as_ptr() const -> const T* { return this->_ok ? &this->value() : nullptr; }
    
    // template <typename F>
    // auto map(F&& f) const -> option<decltype(f(declval<T>()))>
    // {
    //     if (this->_ok) return option<decltype(f(declval<T>()))>(f(this->value()));
    //     return {};
    // }

    template <typename U>
    auto unwrap_or(U&& default_value) const -> T
    {
        return this->_ok ? this->value() : static_cast<T>(forward<U>(default_value));
    }

    template <typename F>
    auto unwrap_or_else(F&& f) const -> T { return this->_ok ? this->value() : f(); }

    void reset()
    {
        if (this->_ok)
        {
            this->value().~T();
            this->_ok = false;
        }
        else
        {
            reinterpret_cast<err<E>*>(_storage._data)->~err<E>();
        }
    }

    private:
    bool _ok;
    storage_type _storage{};
};
}

#endif
