#include "SVector3D.h"
#include "SFloat.h"
#include <cmath>
#include <math.h>

struct SVector3D::Data
{
	float x;
	float y;
	float z;
};

SVector3D::SVector3D()
	:d_(new Data())
{

}


SString SVector3D::toLogString() const
{
	SString ret = (SWS("SVector3D("));
	(ret) << getX() << SWS(", ");
	(ret) << getY() << SWS(", ");
	(ret) << getZ() << SWS(", ");
	(ret) << SWS(")");

	return ret;
}

SVector3D::~SVector3D()
{
	delete d_;
}

SVector3D::SVector3D(float x, float y, float z)
	:SVector3D()
{
	d_->x = x;
	d_->y = y;
	d_->z = z;
}

SVector3D::SVector3D(const SVector3D& obj)
	: SVector3D()
{
	d_->x = obj.getX();
	d_->y = obj.getY();
	d_->z = obj.getZ();
}

float SVector3D::getX() const
{
	return d_->x;
}

float SVector3D::getY() const
{
	return d_->y;
}

float SVector3D::getZ() const
{
	return d_->z;
}

float& SVector3D::getXRef()
{
	return d_->x;
}

float& SVector3D::getYRef()
{
	return d_->y;
}

float& SVector3D::getZRef()
{
	return d_->z;
}

void SVector3D::setX(float x)
{
	d_->x = x;
}

void SVector3D::setY(float y)
{
	d_->y = y;
}

void SVector3D::setZ(float z)
{
	d_->z = z;
}


SVector3D& SVector3D::operator=(const SVector3D& obj)
{
	d_->x = obj.getX();
	d_->y = obj.getY();
	d_->z = obj.getZ();
	return *this;
}


SVector3D SVector3D::operator+(const SVector3D& obj)const
{
	SVector3D ret;

	ret.setX(getX() + obj.getX());
	ret.setY(getY() + obj.getY());
	ret.setZ(getZ() + obj.getZ());

	return ret;
}

SVector3D SVector3D::operator+(float v)const
{
	SVector3D ret;

	ret.setX(getX() + v);
	ret.setY(getY() + v);
	ret.setZ(getZ() + v);

	return ret;
}


SVector3D& SVector3D::operator+=(const SVector3D& obj)
{
	getXRef() += obj.getX();
	getYRef() += obj.getY();
	getZRef() += obj.getZ();
	return *this;
}

SVector3D& SVector3D::operator+=(float v)
{
	getXRef() += v;
	getYRef() += v;
	getZRef() += v;
	return *this;
}

SVector3D SVector3D::operator-(const SVector3D& obj)const
{
	SVector3D ret;

	ret.setX(getX() - obj.getX());
	ret.setY(getY() - obj.getY());
	ret.setZ(getZ() - obj.getZ());

	return ret;
}

SVector3D& SVector3D::operator-=(const SVector3D& obj)
{
	getXRef() -= obj.getX();
	getYRef() -= obj.getY();
	getZRef() -= obj.getZ();
	return *this;
}

SVector3D SVector3D::operator-(float v)const
{
	SVector3D ret;

	ret.setX(getX() - v);
	ret.setY(getY() - v);
	ret.setZ(getZ() - v);

	return ret;
}

SVector3D& SVector3D::operator-=(float v)
{
	getXRef() -= v;
	getYRef() -= v;
	getZRef() -= v;
	return *this;
}



SVector3D SVector3D::operator*(float v)const
{
	SVector3D ret;

	ret.setX(getX() * v);
	ret.setY(getY() * v);
	ret.setZ(getZ() * v);

	return ret;
}

SVector3D& SVector3D::operator*=(float v)
{
	getXRef() *= v;
	getYRef() *= v;
	getZRef() *= v;

	return *this;
}

SVector3D SVector3D::operator/(float v)const
{
	SVector3D ret;

	ret.setX(getX() / v);
	ret.setY(getY() / v);
	ret.setZ(getZ() / v);

	return ret;
}

SVector3D& SVector3D::operator/=(float v)
{
	getXRef() /= v;
	getYRef() /= v;
	getZRef() /= v;

	return *this;
}

SVector3D SVector3D::normalized() const
{
	float len = getX() * getX() +
		getY() * getY() +
		getZ() * getZ();

	if (sFloatIsNull(len - 1.0f))
	{
		return *this;
	}
	else if (!sFloatIsNull(len))
	{
		float sqrtLen =static_cast<float>(std::sqrt(len));
		return *this /(sqrtLen);
	}
	else {
		return SVector3D();
	}
}

float SVector3D::dotProduct(const SVector3D& a, const SVector3D& b)
{
	float ret = 0.0f;

	ret = a.getX() * b.getX()
		+ a.getY() * b.getY()
		+ a.getZ() * b.getZ();

	return ret;
}

SVector3D SVector3D::crossProduct(const SVector3D& a, const SVector3D& b)
{
	SVector3D ret;
	ret.setX(a.getY() * b.getZ() - a.getZ() * b.getY());
	ret.setY(a.getZ() * b.getX() - a.getX() * b.getZ());
	ret.setZ(a.getX() * b.getY() - a.getY() * b.getX());

	return ret;
}

float SVector3D::radian(const SVector3D& a, const SVector3D& b)
{
	return std::acosf(dotProduct(a.normalized(), b.normalized()));
}

float SVector3D::angle(const SVector3D& a, const SVector3D& b)
{
	return radian(a,b)/ SPI_F *180.0f ;
}

