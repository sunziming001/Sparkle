#include "SVertex.h"

struct SVertex::Data
{
	SPointF3D screenPos;
	SPointF2D texturePos;
};


SVertex::SVertex()
	:d_(new Data())
{

}

SVertex::SVertex(const SPointF3D& screenPos,
	const SPointF2D& texturePos)
	:SVertex()
{
	setScreenPos(screenPos);
	setTexturePos(texturePos);
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

SPointF2D SVertex::getTexturePos() const
{
	return d_->texturePos;
}

void SVertex::setScreenPos(const SPointF3D& screenPos)
{
	d_->screenPos = screenPos;
}

void SVertex::setTexturePos(const SPointF2D& texturePos)
{
	d_->texturePos = texturePos;
}

size_t SVertex::GetVertexSize()
{
	return sizeof(SPointF3D)+sizeof(SPointF2D);
}
