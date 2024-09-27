#ifndef _SMOUSE_MOVE_EVENT_H
#define _SMOUSE_MOVE_EVENT_H

#include "SConfig.h"
#include "SEvent.h"
#include <stdint.h>
#include <SPoint.h>

class SPARKLE_API SMouseMoveEvent:public SEvent
{
public:
	SMouseMoveEvent(int32_t x, int32_t y);
	~SMouseMoveEvent();
	SPoint2D getPos()const;
	SStringPtr toLogString()const override;
private:
	DECLARE_INNER_DATA(d_);
};

#endif