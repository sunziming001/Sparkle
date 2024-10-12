#ifndef SMATRIX4X4_H
#define SMATRIX4X4_H

#include "SConfig.h"
#include "SVector4D.h"

class SPARKLE_API SMatrix4x4 {
public:
	SMatrix4x4();
	SMatrix4x4(const SMatrix4x4& obj);
	SMatrix4x4(float data[4][4]);
	~SMatrix4x4();

	void setToIdentity();

	void setValue(int row, int col, float value);
	float getValue(int row, int col)const;
	float& getValueRef(int row, int col);

	SMatrix4x4& operator=(const SMatrix4x4& obj);

	SMatrix4x4 operator+(const SMatrix4x4& obj)const;
	SMatrix4x4 operator+(float v)const;
	SMatrix4x4 operator-(const SMatrix4x4& obj)const;
	SMatrix4x4 operator-(float v)const;

	SMatrix4x4 operator*(const SMatrix4x4& obj)const;
	SVector4D operator*(const SVector4D& obj)const;
	SMatrix4x4 operator*(float v)const;

	SMatrix4x4 operator/(float v)const;

	SMatrix4x4& operator+=(const SMatrix4x4& obj);
	SMatrix4x4& operator+=(float v);

	SMatrix4x4& operator-=(const SMatrix4x4& obj);
	SMatrix4x4& operator-=(float v);

	SMatrix4x4& operator*=(const SMatrix4x4& obj);
	SMatrix4x4& operator*=(float v);

	SMatrix4x4 operator/=(float v);
private:
	DECLARE_INNER_DATA(d_);
};


#endif
