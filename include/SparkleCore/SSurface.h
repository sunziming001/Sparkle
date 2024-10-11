#ifndef _SSURFACE_H
#define _SSURFACE_H

#include "SConfig.h"
#include "SVertex.h"
#include "SByteArray.h"
#include "SSharedPtr.h"
#include "SString.h"

class SPARKLE_API SSurface
{
public:
	SSurface(uint32_t vertexCnt);
	~SSurface();
	uint32_t getVertexCnt();
	uint32_t getTriangleCnt()const;
	const uint32_t* getVertexDrawOrder()const;
	size_t getVertexDrawOrderSize()const;
	size_t getVertexDrawOrderCnt()const;
	void setVertex(uint32_t index, const SVertex& vertex);
	SByteArrayPtr getVertexData();
	
	void loadTextureFromResPack(const SString& resPath);
	uint32_t getTextureChannels()const;
	uint32_t getTextureWidth()const;
	uint32_t getTextureHeight()const;
	unsigned char* getTextureData()const;
private:
	DECLARE_INNER_DATA(d_);

};

typedef SSharedPtr<SSurface> SSurfacePtr;

#endif