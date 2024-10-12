#ifndef _STRANSFORM_H
#define _STRANSFORM_H

#include "SConfig.h"
#include "SVector3D.h"

class SPARKLE_API STransform
{
public:
	STransform();
	~STransform();

	void scale(const SVector3D& v);
	void move(const SVector3D& v);

	void angleRotate(const SVector3D& v);
	void angleRotateX(float v);
	void angleRotateY(float v);
	void angleRotateZ(float v);

	void radianRotate(const SVector3D& v);

	void radianRotateX(float v);
	void radianRotateY(float v);
	void radianRotateZ(float v);

	SVector3D calc(const SVector3D& origin);
private:
	DECLARE_INNER_DATA(d_);

};


#endif

