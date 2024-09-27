#ifndef _SFLAGS_H
#define _SFLAGS_H

#include "SConfig.h"
#include <stdint.h>

template<typename T>
class SFlags {
public:

	SFlags()
		:value_(0)
	{
		
	}

	SFlags(T value)
	{
		value_ = static_cast<uint32_t>(value);
	}

	SFlags(const SFlags& _other)
		:value_(_other.value_)
	{

	}

	SFlags& operator=(const T& value)
	{
		this->value_ = value;
		return *this;
	}

	SFlags& operator=(const SFlags& _other)
	{
		this->value_ = _other.value_;
		return *this;
	}

	SFlags operator|(const SFlags& _other)
	{
		SFlags ret;
		ret.value_ = this->value_ | _other.value_;
		return ret;
	}

	SFlags& operator|=(const SFlags& _other)
	{
		this->value_ |= _other.value_;
		return *this;
	}

	SFlags operator&(const SFlags& _other)
	{
		SFlags ret;
		ret.value_ = this->value_ & _other.value_;
		return ret;
	}

	SFlags operator!()
	{
		SFlags ret;
		ret.value_ = !(this->value_);

		return ret;
	}

	SFlags& operator&=(const SFlags& _other)
	{
		this->value_ &= _other.value_;
		return *this;
	}


	explicit operator bool()
	{
		return value_ != 0;
	}

	~SFlags()
	{

	}
private:
	uint32_t value_;

};


#endif
