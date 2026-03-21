///-----------------------------------------------------------------------------
/// MarineTelematics Template Library               - (c) 2026 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file function.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 20-03-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_FUNCTION_H
#define MTL_FUNCTION_H

#include <new>
#include <cstring>
#include <utility>
#include <type_traits>

namespace mtl
{
template<size_t Size, typename>
class function;

template<size_t Size, typename R, typename... Args>
class function<Size, R(Args...)>
{
    public:
    function() = default;

    template<typename F>
    function(F f)
    {
        static_assert(sizeof(F) <= Size, "Callable too large");
        static_assert(std::is_invocable_r_v<R, F&, Args...>,
                      "Callable has incompatible signature");

        new (this->_storage) F(std::move(f));

        this->_invoke = [](void* data, Args... args) -> R
        {
            return (*reinterpret_cast<F*>(data))(std::forward<Args>(args)...);
        };

        if constexpr (!std::is_trivially_destructible_v<F>)
        {
            _destroy = [](void* data)
            {
                reinterpret_cast<F*>(data)->~F();
            };
        }
        else
        {
            _destroy = nullptr; // no-op
        }
    }

    function(const function&) = delete;
    function& operator=(const function&) = delete;

    function(function &&other) noexcept
    {
        this->move_from(std::move(other));
    }

    function& operator=(function &&other) noexcept
    {
        if (this != &other)
        {
            this->reset();
            this->move_from(std::move(other));
        }

        return *this;
    }

    ~function() { this->reset(); }

    explicit operator bool() const
    {
        return this->_invoke != nullptr;
    }

    R operator()(Args... args)
    {
        return this->_invoke(this->_storage, std::forward<Args>(args)...);
    }

    void reset()
    {
        if (this->_destroy)
        {
            this->_destroy(_storage);
        }

        this->_invoke = nullptr;
        this->_destroy = nullptr;
    }

    private:
    alignas(std::max_align_t) unsigned char _storage[Size];

    R (*_invoke)(void*, Args...) = nullptr;
    void (*_destroy)(void*) = nullptr;

    void move_from(function&& other)
    {
        if (other._invoke)
        {
            std::memcpy(_storage, other._storage, Size);
            this->_invoke = other._invoke;
            this->_destroy = other._destroy;

            other._invoke = nullptr;
            other._destroy = nullptr;
        }
    }
};
}

#endif
