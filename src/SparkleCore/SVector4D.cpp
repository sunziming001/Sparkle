#include "SVector4D.h"

struct SVector4D::Data
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 0.0f;
};

SVector4D::SVector4D()
	:d_(new Data())
{

}


SVector4D::~SVector4D()
{
	delete d_;
}

SVector4D::SVector4D(float x, float y, float z, float w)
	:SVector4D()
{
	d_->x = x;
	d_->y = y;
	d_->z = z;
	d_->w = w;
}

SVector4D::SVector4D(const SVector4D& v)
	:SVector4D()
{
	d_->x = v.getX();
	d_->y = v.getY();
	d_->z = v.getZ();
	d_->w = v.getW();
}

float SVector4D::getX() const
{
	return d_->x;
}

float SVector4D::getY() const
{
	return d_->y;
}

float SVector4D::getZ() const
{
	return d_->z;
}

float SVector4D::getW() const
{
	return d_->w;
}


float& SVector4D::getXRef()
{
	return d_->x;
}

float& SVector4D::getYRef()
{
	return d_->y;
}

float& SVector4D::getZRef()
{
	return d_->z;
}

float& SVector4D::getWRef()
{
	return d_->w;
}

void SVector4D::setX(float v)
{
	d_->x = v;
}

void SVector4D::setY(float v)
{
	d_->y = v;
}

void SVector4D::setZ(float v)
{
	d_->z = v;
}

void SVector4D::setW(float v)
{
	d_->w = v;
}

SVector4D& SVector4D::operator=(const SVector4D& v)
{
	d_->x = v.getX();
	d_->y = v.getY();
	d_->z = v.getZ();
	d_->w = v.getW();

	return *this;
}


SVector4D SVector4D::operator+(const SVector4D& v)
{
	SVector4D ret;
	ret.setX(getX() + v.getX());
	ret.setY(getY() + v.getY());
	ret.setZ(getZ() + v.getZ());
	ret.setW(getW() + v.getW());

	return ret;
}


SVector4D SVector4D::operator+(float factor)
{
	SVector4D ret;
	ret.setX(getX() + factor);
	ret.setY(getY() + factor);
	ret.setZ(getZ() + factor);
	ret.setW(getW() + factor);

	return ret;
}

SVector4D SVector4D::operator-(const SVector4D& v)
{
	SVector4D ret;
	ret.setX(getX() - v.getX());
	ret.setY(getY() - v.getY());
	ret.setZ(getZ() - v.getZ());
	ret.setW(getW() - v.getW());

	return ret;
}

SVector4D SVector4D::operator-(float factor)
{
	SVector4D ret;
	ret.setX(getX() - factor);
	ret.setY(getY() - factor);
	ret.setZ(getZ() - factor);
	ret.setW(getW() - factor);

	return ret;
}

SVector4D SVector4D::operator*(float factor)
{
	SVector4D ret;
	ret.setX(getX() * factor);
	ret.setY(getY() * factor);
	ret.setZ(getZ() * factor);
	ret.setW(getW() * factor);

	return ret;
}

SVector4D SVector4D::operator/(float factor)
{
	SVector4D ret;
	ret.setX(getX() / factor);
	ret.setY(getY() / factor);
	ret.setZ(getZ() / factor);
	ret.setW(getW() / factor);

	return ret;
}

