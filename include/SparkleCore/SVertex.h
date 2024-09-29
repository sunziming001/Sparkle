#ifndef _SVERTEX_H
#define _SVERTEX_H

#include "SConfig.h"
#include "SByteArray.h"
#include "SPoint.h"

class SPARKLE_API SVertex
{
public:
	SVertex();
	SVertex(const SPointF3D& screenPos);
	SVertex(const SVertex& _other);
	~SVertex();

	const SVertex& operator=(const SVertex& _other);

	SPointF3D getScreenPos()const;
	void setScreenPos(const SPointF3D& screenPos);

	static size_t GetVertexSize();
private:
	DECLARE_INNER_DATA(d_);
};

#endif