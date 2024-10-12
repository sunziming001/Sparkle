#ifndef SVECTOR4D_H
#define SVECTOR4D_H

#include "SConfig.h"
#include "SPoint.h"
#include "SLoggable.h"

class SPARKLE_API SVector4D:public SLoggable
{
public:
	SVector4D();
	~SVector4D();
	SVector4D(float x, float y, float z, float w);
	SVector4D(const SVector4D& v);
	
	SString toLogString()const override;

	float getX()const;
	float getY()const;
	float getZ()const;
	float getW()const;

	float& getXRef();
	float& getYRef();
	float& getZRef();
	float& getWRef();

	void setX(float v);
	void setY(float v);
	void setZ(float v);
	void setW(float v);


	SVector4D& operator=(const SVector4D& obj);

	SVector4D operator+(const SVector4D& obj)const;
	SVector4D operator+(float factor)const;

	SVector4D operator-(const SVector4D& obj)const;
	SVector4D operator-(float factor)const;

	SVector4D operator*(float factor)const;
	SVector4D operator/(float factor)const;

	SVector4D& operator+=(const SVector4D& obj);
	SVector4D& operator+=(float v);
	
	SVector4D& operator-=(const SVector4D& obj);
	SVector4D& operator-=(float v);

	SVector4D& operator*=(float v);
	SVector4D& operator/=(float v);
private:
	DECLARE_INNER_DATA(d_);
};


#endif