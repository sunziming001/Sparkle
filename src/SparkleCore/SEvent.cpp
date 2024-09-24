#include "SEvent.h"

SEvent::SEvent(const SEventType& type)
	:type_(type)
{

}

SEvent::~SEvent()
{

}

SEventType SEvent::getEventType() const
{
	return type_;
}
