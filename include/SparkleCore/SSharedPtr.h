#ifndef _SSHAREDPTR_H
#define _SSHAREDPTR_H

#include "SConfig.h"
#include <stdint.h>

typedef uint32_t RefCntType;

template<class T>
class SShardPtr {
public:
	SShardPtr(T* ptr)
	{
		ptr_ = ptr;
		refCntPtr_ = new RefCntType;
		*refCntPtr_ = 1;
	}

	SShardPtr()
	{
		ptr_ = nullptr;
		refCntPtr_ = new RefCntType;
		*refCntPtr_ = 0;
	}

	SShardPtr(const SShardPtr& _other)
	{
		ptr_ = _other.ptr_;
		refCntPtr_ = _other.refCntPtr_;

		(*refCntPtr_)++;
	}

	~SShardPtr()
	{
		(*refCntPtr_)--;
		if (*refCntPtr_ == 0)
		{
			delete refCntPtr_;
			delete ptr_;

			refCntPtr_ = nullptr;
			ptr_ = nullptr;
		}
	}

	SShardPtr operator=(const SShardPtr& _other)
	{
		SShardPtr ret(_other);

		return ret;
	}

	SShardPtr operator=(T* ptr)
	{
		SShardPtr ret(ptr);

		return ret;
	}

	RefCntType getCount()const
	{
		return *refCntPtr_;
	}

	T* getPtr()const
	{
		return ptr_;
	}


	bool operator==(const SShardPtr& _other)
	{
		return this->ptr_ == _other->ptr_;
	}

	explicit operator bool()
	{
		return getCount() != 0;
	}

	T* operator->()const
	{
		return this->ptr_;
	}

private:
	T* ptr_;
	RefCntType* refCntPtr_;
};

#endif