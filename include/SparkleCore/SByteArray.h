#ifndef _S_BYTE_ARRAY_H
#define _S_BYTE_ARRAY_H

#include "SConfig.h"
#include "stdint.h"

typedef uint8_t SByte;
typedef size_t SByteSize;
#define DEFAULT_BYTE_ARRAY_SIZE 4

class SPARKLE_API SByteArray
{
public:
	SByteArray(size_t size= DEFAULT_BYTE_ARRAY_SIZE);
	SByteArray(SByte* data, SByteSize size);
	SByteArray(const SByteArray& _other);
	~SByteArray();
	SByte* data()const;
	SByteSize size()const;
	const SByteArray& operator=(const SByteArray&);
private:
	void cleanup();
private:
	SByte* ptr_=nullptr;
	SByteSize size_ = 0;

};


#endif