#include "SByteArray.h"
#include <algorithm>

SByteArray::SByteArray(size_t size/*= DEFAULT_BYTE_ARRAY_SIZE*/)
	:ptr_(new SByte[size])
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

void SByteArray::cleanup()
{
	delete[] ptr_;
}

const SByteArray& SByteArray::operator=(const SByteArray& _other)
{
	cleanup();
	ptr_ = new SByte[_other.size()];
	size_ = _other.size();
	memcpy(ptr_, _other.data(), _other.size());

	return *this;
}
