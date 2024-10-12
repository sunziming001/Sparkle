#include "SMatrix4x4.h"
#include <string>

struct SMatrix4x4::Data
{
	float m[4][4] = {0.0f};
};

SMatrix4x4::SMatrix4x4()
	:d_(new Data())
{

}

SMatrix4x4::SMatrix4x4(float data[4][4])
	:SMatrix4x4()
{
	memcpy(d_->m, data, sizeof(float) * 16);
}

SMatrix4x4::SMatrix4x4(const SMatrix4x4& obj)
	: SMatrix4x4()
{
	memcpy(d_->m, obj.d_->m, sizeof(float) * 16);
}

SMatrix4x4::~SMatrix4x4()
{
	delete d_;
}

void SMatrix4x4::setToIdentity()
{
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (row == col)
			{
				getValueRef(row, col) = 1.0f;
			}
			else {
				getValueRef(row, col) = 0.0f;
			}
		}
	}
}

void SMatrix4x4::setValue(int row, int col, float value)
{
	d_->m[row][col] = value;
}

float SMatrix4x4::getValue(int row, int col) const
{
	return d_->m[row][col];
}

float& SMatrix4x4::getValueRef(int row, int col)
{
	return d_->m[row][col];
}

SMatrix4x4& SMatrix4x4::operator=(const SMatrix4x4& obj)
{
	memcpy(d_->m, obj.d_->m, sizeof(float) * 16);
	return *this;
}

SMatrix4x4 SMatrix4x4::operator+(const SMatrix4x4& obj)const
{
	SMatrix4x4 ret;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			ret.getValueRef(row, col) = getValue(row, col) + obj.getValue(row, col);
		}
	}

	return ret;
}

SMatrix4x4 SMatrix4x4::operator+(float v) const
{
	SMatrix4x4 ret;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			ret.getValueRef(row, col) = getValue(row, col) + v;
		}
	}

	return ret;
}

SMatrix4x4 SMatrix4x4::operator-(const SMatrix4x4& obj)const
{
	SMatrix4x4 ret;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			ret.getValueRef(row, col) = getValue(row, col) - obj.getValue(row, col);
		}
	}

	return ret;
}

SMatrix4x4 SMatrix4x4::operator-(float v) const
{
	SMatrix4x4 ret;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			ret.getValueRef(row, col) = getValue(row, col) - v;
		}
	}

	return ret;
}

SMatrix4x4 SMatrix4x4::operator*(const SMatrix4x4& obj) const
{
	SMatrix4x4 ret;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			ret.getValueRef(row, col) = getValue(row, 0) * obj.getValue(0, col)
				+ getValue(row, 1) * obj.getValue(1, col)
				+ getValue(row, 2) * obj.getValue(2, col)
				+ getValue(row, 3) * obj.getValue(3, col);
		}
	}

	return ret;
}

SMatrix4x4 SMatrix4x4::operator*(float v) const
{
	SMatrix4x4 ret;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			ret.getValueRef(row, col) *= v;
		}
	}

	return ret;
}

SVector4D SMatrix4x4::operator*(const SVector4D& obj) const
{
	SVector4D ret;

	ret.getXRef() = getValue(0, 0) * obj.getX()
		+ getValue(0, 1) * obj.getY()
		+ getValue(0, 2) * obj.getZ()
		+ getValue(0, 3) * obj.getW();

	ret.getYRef() = getValue(1, 0) * obj.getX()
		+ getValue(1, 1) * obj.getY()
		+ getValue(1, 2) * obj.getZ()
		+ getValue(1, 3) * obj.getW();

	ret.getZRef() = getValue(2, 0) * obj.getX()
		+ getValue(2, 1) * obj.getY()
		+ getValue(2, 2) * obj.getZ()
		+ getValue(2, 3) * obj.getW();

	ret.getWRef() = getValue(3, 0) * obj.getX()
		+ getValue(3, 1) * obj.getY()
		+ getValue(3, 2) * obj.getZ()
		+ getValue(3, 3) * obj.getW();

	return ret;
}

SMatrix4x4 SMatrix4x4::operator/(float v) const
{
	SMatrix4x4 ret;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			ret.getValueRef(row, col) /= v;
		}
	}

	return ret;
}


SMatrix4x4& SMatrix4x4::operator+=(float v)
{
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			getValueRef(row, col) += v;
		}
	}
	return *this;
}

SMatrix4x4& SMatrix4x4::operator+=(const SMatrix4x4& obj)
{
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			getValueRef(row, col) += obj.getValue(row, col);
		}
	}
	return *this;
}


SMatrix4x4& SMatrix4x4::operator-=(float v)
{
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			getValueRef(row, col) -= v;
		}
	}
	return *this;
}

SMatrix4x4& SMatrix4x4::operator-=(const SMatrix4x4& obj)
{
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			getValueRef(row, col) -= obj.getValue(row, col);
		}
	}
	return *this;
}


SMatrix4x4& SMatrix4x4::operator*=(const SMatrix4x4& obj)
{
	SMatrix4x4 ret = (*this) * obj;
	*this = ret;

	return *this;
}

SMatrix4x4& SMatrix4x4::operator*=(float v)
{
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			getValueRef(row, col) *= v;
		}
	}
	return *this;
}


SMatrix4x4 SMatrix4x4::operator/=(float v) 
{
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			getValueRef(row, col) /= v;
		}
	}
	return *this;
}