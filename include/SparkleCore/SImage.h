#ifndef _SIMAGE_H
#define _SIMAGE_H

#include "SConfig.h"
#include "SString.h"
#include "SSize.h"


class SPARKLE_API SImage
{
public:
	SImage();
	~SImage();
	SSize2D getImageSize()const;
	uint32_t getImageWidth()const;
	uint32_t getImageHeight()const;
	uint32_t getChannels()const;
	void loadFromResPack(const SString& path);
	
	unsigned char* getDataPtr()const;
	size_t getDataSize()const;
private:
	DECLARE_INNER_DATA(d_);
};


#endif