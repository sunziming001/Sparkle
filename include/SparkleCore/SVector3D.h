#ifndef _SVECTOR3D_H
#define _SVECTOR3D_H

#include "SConfig.h"
#include "SLoggable.h"

class SPARKLE_API SVector3D: public SLoggable
{
public:
	SVector3D();
	~SVector3D();
	SVector3D(float x, float y, float z);
	SVector3D(const SVector3D& obj);

	SString toLogString()const override;

	float getX()const;
	float getY()const;
	float getZ()const;

	float &getXRef();
	float &getYRef();
	float &getZRef();

	void setX(float x);
	void setY(float y);
	void setZ(float z);

	SVector3D& operator=(const SVector3D& obj);

	SVector3D operator+(const SVector3D& obj)const;
	SVector3D operator+(float v)const;

	SVector3D& operator+=(const SVector3D& obj);
	SVector3D& operator+=(float v);

	SVector3D operator-(const SVector3D& obj)const;
	SVector3D operator-(float v)const;

	SVector3D& operator-=(const SVector3D& obj);
	SVector3D& operator-=(float v);

	SVector3D operator*(float v)const;
	SVector3D &operator*=(float v);

	SVector3D operator/(float v)const;
	SVector3D& operator/=(float v);

	SVector3D normalized()const;
	static float dotProduct(const SVector3D& a, const SVector3D& b);
	static SVector3D crossProduct(const SVector3D& a, const SVector3D& b);
	static float radian(const SVector3D& a, const SVector3D& b);
	static float angle(const SVector3D& a, const SVector3D& b);
private:
	DECLARE_INNER_DATA(d_);
};

#endif

