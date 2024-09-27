#ifndef _SSHAREDPTR_H
#define _SSHAREDPTR_H

#include "SConfig.h"
#include <stdint.h>

typedef uint32_t RefCntType;

template<class T>
class SSharedPtr {
public:
	using element_type = T;
	SSharedPtr(T* ptr)
	{
		ptr_ = ptr;
		refCntPtr_ = new RefCntType;
		*refCntPtr_ = 1;
	}

	SSharedPtr()
	{
		ptr_ = nullptr;
		refCntPtr_ = new RefCntType;
		*refCntPtr_ = 0;
	}

	SSharedPtr(const SSharedPtr& _other)
	{
		ptr_ = _other.ptr_;
		refCntPtr_ = _other.refCntPtr_;

		(*refCntPtr_)++;
	}

	
	SSharedPtr(T* ptr, RefCntType *refCntPtr)
	{
		ptr_ = ptr;
		refCntPtr_ = refCntPtr;

		(*refCntPtr_)++;
	}

	~SSharedPtr()
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

	T& operator*()
	{
		return *ptr_;
	}

	SSharedPtr& operator=(const SSharedPtr& _other)
	{
		ptr_ = _other.ptr_;
		refCntPtr_ = _other.refCntPtr_;

		(*refCntPtr_)++;
		return *this;
	}

	SSharedPtr operator=(T* ptr)
	{
		SSharedPtr ret(ptr);

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


	bool operator==(const SSharedPtr& _other)
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

	RefCntType* getRefCntPtr()const
	{
		return this->refCntPtr_;
	}
private:
	T* ptr_;
	RefCntType* refCntPtr_;
};


template<class ChildClz, class BaseClz>
SSharedPtr<ChildClz> spk_dynamic_pointer_cast(SSharedPtr<BaseClz> _Other)
{
	ChildClz *_Ptr = dynamic_cast<ChildClz*>(_Other.getPtr());
	SSharedPtr<ChildClz> ret;
	if (_Ptr)
	{
		ret = SSharedPtr<ChildClz>(_Ptr, _Other.getRefCntPtr());
	}
	return ret;
}

#endif