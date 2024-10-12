#include "STransform.h"
#include "SMatrix4x4.h"
#include "SFloat.h"
#include <cmath>

struct STransform::Data {
	SMatrix4x4 transMatrix;
};

STransform::STransform()
	:d_(new Data())
{
	d_->transMatrix.setToIdentity();
}

STransform::~STransform()
{
	delete d_;
}

void STransform::scale(const SVector3D& v)
{
	SMatrix4x4 mat;
	mat.setToIdentity();

	mat.getValueRef(0, 0) = v.getX();
	mat.getValueRef(1, 1) = v.getY();
	mat.getValueRef(2, 2) = v.getZ();

	d_->transMatrix *= mat;
}

void STransform::move(const SVector3D& v)
{
	SMatrix4x4 mat;
	mat.setToIdentity();

	mat.getValueRef(0, 3) = v.getX();
	mat.getValueRef(1, 3) = v.getY();
	mat.getValueRef(2, 3) = v.getZ();

	d_->transMatrix *= mat;
}

void STransform::angleRotate(const SVector3D& v)
{
	SVector3D radian;
	radian.getXRef() = v.getX() * SPI_F / 180.0f;
	radian.getYRef() = v.getY() * SPI_F / 180.0f;
	radian.getZRef() = v.getZ() * SPI_F / 180.0f;

	radianRotate(radian);
}

void STransform::angleRotateX(float v)
{
	radianRotateX(v* SPI_F / 180.0f);
}

void STransform::angleRotateY(float v)
{
	radianRotateY(v * SPI_F / 180.0f);
}

void STransform::angleRotateZ(float v)
{
	radianRotateZ(v * SPI_F / 180.0f);
}

void STransform::radianRotate(const SVector3D& v)
{
	radianRotateX(v.getX());
	radianRotateY(v.getY());
	radianRotateZ(v.getZ());
}

void STransform::radianRotateX(float v)
{
	SMatrix4x4 mat;
	mat.setToIdentity();

	mat.getValueRef(1, 1) = std::cosf(v);
	mat.getValueRef(1, 2) = std::sinf(v)*-1.0f;

	mat.getValueRef(2, 1) = std::sinf(v);
	mat.getValueRef(2, 2) = std::cosf(v);

	d_->transMatrix *= mat;
}

void STransform::radianRotateY(float v)
{
	SMatrix4x4 mat;
	mat.setToIdentity();

	mat.getValueRef(0, 0) = std::cosf(v);
	mat.getValueRef(0, 2) = std::sinf(v) ;

	mat.getValueRef(2, 0) = std::sinf(v) * -1.0f;
	mat.getValueRef(2, 2) = std::cosf(v);

	d_->transMatrix *= mat;
}

void STransform::radianRotateZ(float v)
{
	SMatrix4x4 mat;
	mat.setToIdentity();

	mat.getValueRef(0, 0) = std::cosf(v);
	mat.getValueRef(0, 1) = std::sinf(v) * -1.0f;

	mat.getValueRef(1, 0) = std::sinf(v);
	mat.getValueRef(1, 1) = std::cosf(v);


	d_->transMatrix *= mat;
}

SVector3D STransform::calc(const SVector3D& origin)
{
	SVector4D v(origin.getX(), origin.getY(), origin.getZ(), 1.0f);
	SVector4D ret = d_->transMatrix * v;

	return SVector3D(ret.getX(), ret.getY(), ret.getZ());
}

