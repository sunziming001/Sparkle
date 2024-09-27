#include "SMouseMoveEvent.h"

struct SMouseMoveEvent::Data
{
	SPoint2D pos;
};

SMouseMoveEvent::SMouseMoveEvent(int32_t x, int32_t y)
	:SEvent(SEventType::MouseMove)
	,d_(new Data())
{
	d_->pos.x = x;
	d_->pos.y = y;
}

SMouseMoveEvent::~SMouseMoveEvent()
{
	delete d_;
}

SPoint2D SMouseMoveEvent::getPos() const
{
	return d_->pos;
}

SStringPtr SMouseMoveEvent::toLogString() const
{
	SStringPtr ret = SEvent::toLogString();
	(*ret) << SWS("{");
	(*ret) << SWS("x: ") << d_->pos.x << SWS(", ");
	(*ret) << SWS("y: ") << d_->pos.y << SWS(", ");
	(*ret) << SWS("}");

	return ret;
}

