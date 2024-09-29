#include "SByteArray.h"
#include <algorithm>

SByteArray::SByteArray(size_t size/*= DEFAULT_BYTE_ARRAY_SIZE*/)
	:ptr_(size==0? nullptr : new SByte[size])
	,size_(size)
{

}

SByteArray::SByteArray(const SByteArray& _other)
{
	ptr_ = new SByte[_other.size()];
	size_ = _other.size();
	memcpy(ptr_, _other.data(), _other.size());
}

SByteArray::SByteArray(SByte* data, SByteSize size)
	:ptr_(new SByte[size])
	, size_(size)
{
	memcpy(ptr_, data, size);
}

SByteArray::~SByteArray()
{
	cleanup();
}

SByte* SByteArray::data() const
{
	return ptr_;
}

SByteSize SByteArray::size() const
{
	return size_;
}



SByteArray& SByteArray::operator=(const SByteArray& _other)
{
	cleanup();
	ptr_ = new SByte[_other.size()];
	size_ = _other.size();
	memcpy(ptr_, _other.data(), _other.size());

	return *this;
}


SByteArray SByteArray::operator+(const SByteArray& _other)
{
	SByteArray ret(size()+_other.size());

	memcpy(ret.ptr_, this->ptr_, size());
	memcpy(ret.ptr_ + size(), _other.data(), _other.size());

	return ret;
}


SByteArray& SByteArray::operator+=(const SByteArray& _other)
{
	SByte* newPtr = new SByte[size() + _other.size()];

	if (ptr_)
	{
		memcpy(newPtr, this->ptr_, size());
	}
	
	memcpy(newPtr + size(), _other.data(), _other.size());

	delete[] this->ptr_;

	this->ptr_ = newPtr;
	this->size_ += _other.size();

	return *this;
}

void SByteArray::writeData(SByteSize destPos, const void* dataPtr, SByteSize dataSize)
{
	if (destPos < size()
		&& destPos + dataSize <= size())
	{
		memcpy(this->ptr_ + destPos, dataPtr, dataSize);
	}
}

SByteArray& SByteArray::operator-=(size_t size)
{
	if (size <= size_)
	{
		size_ -= size;

		SByte* newPtr = new SByte[size_];
		memcpy(newPtr, this->ptr_, size_);

		delete[] this->ptr_;
		this->ptr_ = newPtr;
	}
	return *this;
}

void SByteArray::cleanup()
{
	delete[] ptr_;
}