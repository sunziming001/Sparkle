#ifndef SACTIVE_EVENT_H
#define SACTIVE_EVENT_H

#include "SConfig.h"
#include "SEvent.h"


class SActiveEvent :public SEvent
{
public:
	SActiveEvent(bool isActive);
	virtual ~SActiveEvent();
	bool getIsActive();
private:
	bool isActive_;
};

#endif