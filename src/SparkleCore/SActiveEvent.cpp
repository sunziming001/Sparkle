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
