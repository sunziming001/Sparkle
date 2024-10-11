#ifndef _SVERTEX_H
#define _SVERTEX_H

#include "SConfig.h"
#include "SByteArray.h"
#include "SPoint.h"

class SPARKLE_API SVertex
{
public:
	SVertex();
	SVertex(const SPointF3D& screenPos,const SPointF2D& texturePos);
	SVertex(const SVertex& _other);
	~SVertex();

	const SVertex& operator=(const SVertex& _other);

	SPointF3D getScreenPos()const;
	SPointF2D getTexturePos()const;

	void setScreenPos(const SPointF3D& screenPos);
	void setTexturePos(const SPointF2D& texturePos);

	static size_t GetVertexSize();
private:
	DECLARE_INNER_DATA(d_);
};

#endif