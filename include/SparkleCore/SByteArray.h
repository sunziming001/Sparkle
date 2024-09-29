#ifndef _S_BYTE_ARRAY_H
#define _S_BYTE_ARRAY_H

#include "SConfig.h"
#include "stdint.h"
#include "SSharedPtr.h"

typedef uint8_t SByte;
typedef size_t SByteSize;

class SPARKLE_API SByteArray
{
public:
	SByteArray(size_t size=0);
	SByteArray(SByte* data, SByteSize size);
	SByteArray(const SByteArray& _other);
	~SByteArray();
	SByte* data()const;
	SByteSize size()const;
	SByteArray& operator=(const SByteArray&);
	SByteArray operator+(const SByteArray& _other);
	SByteArray& operator+=(const SByteArray& _other);

	SByteArray& operator-=(size_t size);

	void writeData(SByteSize destPos, const void* dataPtr, SByteSize dataSize);
private:
	void cleanup();
private:
	SByte* ptr_=nullptr;
	SByteSize size_ = 0;

};

typedef SSharedPtr<SByteArray> SByteArrayPtr;

#endif