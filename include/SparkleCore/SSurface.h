#ifndef _SSURFACE_H
#define _SSURFACE_H

#include "SConfig.h"
#include "SVertex.h"
#include "SByteArray.h"
#include "SSharedPtr.h"

class SPARKLE_API SSurface
{
public:
	SSurface(uint32_t vertexCnt);
	~SSurface();
	uint32_t getVertexCnt();
	void setVertex(uint32_t index, const SVertex& vertex);
	SByteArrayPtr toByteArrayPtr();
private:
	DECLARE_INNER_DATA(d_);

};

typedef SSharedPtr<SSurface> SSurfacePtr;

#endif