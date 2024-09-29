#include "SEvent.h"

struct SEvent::Data {
	uint32_t id;
	SEventType type;
};

SEvent::SEvent(const SEventType& type)
	:d_(new Data)
{
	static uint32_t SEVENT_ID = 0;
	SEVENT_ID++;

	d_->id = SEVENT_ID;
	d_->type = type;
}

SEvent::~SEvent()
{

}

SEventType SEvent::getEventType() const
{
	return d_->type;
}

SStringPtr SEvent::toLogString() const
{
	SStringPtr ret = new SString(SWS("SEvent("));
	(*ret) << EventTypeToString(d_->type);
	(*ret) << SWS(")@");
	(*ret) << d_->id;

	return ret;
}

uint32_t SEvent::getId() const
{
	return d_->id;
}

SStringPtr SEvent::EventTypeToString(SEventType tp)
{
	SStringPtr ret = new SString();
	switch (tp)
	{
	case SEventType::Active:
		(*ret) << SWS("Active");
		break;
	case SEventType::Close:
		(*ret) << SWS("Close");
		break;
	case SEventType::MouseMove:
		(*ret) << SWS("MouseMove");
		break;
	case SEventType::Key:
		(*ret) << SWS("Key");
		break;
	case SEventType::None:
	default:
		(*ret) << SWS("None");

		break;
	}


	return ret;
}
