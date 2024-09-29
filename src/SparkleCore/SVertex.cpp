#include "SVertex.h"

struct SVertex::Data
{
	SPointF3D screenPos;
};


SVertex::SVertex()
	:d_(new Data())
{

}

SVertex::SVertex(const SPointF3D& screenPos)
	:SVertex()
{
	setScreenPos(screenPos);
}


SVertex::SVertex(const SVertex& _other)
	:SVertex()
{
	*d_ = *(_other.d_);
}

SVertex::~SVertex()
{
	delete d_;
}

const SVertex& SVertex::operator=(const SVertex& _other)
{
	*d_ = *(_other.d_);
	return *this;
}

SPointF3D SVertex::getScreenPos() const
{
	return d_->screenPos;
}

void SVertex::setScreenPos(const SPointF3D& screenPos)
{
	d_->screenPos = screenPos;
}

size_t SVertex::GetVertexSize()
{
	return sizeof(SPointF3D);
}
