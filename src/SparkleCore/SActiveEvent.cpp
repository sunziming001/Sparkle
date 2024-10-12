#include "SActiveEvent.h"

SActiveEvent::SActiveEvent(bool isActive)
	:SEvent(SEventType::Active)
	,isActive_(isActive)
{

}

SActiveEvent::~SActiveEvent()
{

}

bool SActiveEvent::getIsActive()
{
	return isActive_;
}

SString SActiveEvent::toLogString() const
{
	SString ret = SEvent::toLogString();
	(ret) << SWS("{");
	(ret) << "isActive: " << isActive_<<";";
	(ret) << SWS("}");
	return ret;
}
