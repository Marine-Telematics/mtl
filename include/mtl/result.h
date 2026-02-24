///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2025 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file result.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 22-02-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_RESULT_H
#define MTL_RESULT_H

#include <cstddef>

#include "utility.h"
#include "type_traits.h"

namespace mtl
{
template<typename E>
struct err
{
	E _value;
	constexpr err() = default;
	constexpr err(E&& e) : _value(e) {};
};


template<typename T, typename E>
class result
{
	public:
	using ok_type  = T;
	using err_type = mtl::err<E>;

	template<class ...Args>
	constexpr result(Args&&...args)
	{
		this->_ok = true;
		new (&this->_value._ok) T(forward<Args>(args)...);
	}

	constexpr result(ok_type &&val)
	{
		this->_ok = true;
		this->_value._ok = move(val);
	}

	constexpr result(const err_type &e)
	{
		this->_ok = false;
		this->_value._err = e;
	}

	constexpr result(err_type &&e)
	{
		this->_ok = false;
		this->_value._err = move(e);
	}

	constexpr auto is_ok() const -> bool { return this->_ok; }
	constexpr auto is_err() const -> bool { return !(this->_ok); }

	constexpr auto ok() -> ok_type& { return this->_value._ok; }
	constexpr auto ok() const -> const ok_type& { return this->_value._ok; }

	constexpr auto err() -> err_type& { return this->_value._err; }
	constexpr auto err() const -> const err_type& { return this->_value._err; }

	private:
	bool _ok = false;

	union
	{
		err_type _err;
		ok_type _ok;
	} _value;
};
}

#endif
