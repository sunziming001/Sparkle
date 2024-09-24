#ifndef _SEVENT_H
#define _SEVENT_H

#include "SConfig.h"

enum class SPARKLE_API SEventType
{
	None,
	Active,
	Close,
	MouseMove,
	MouseButton,
	Keyboard,
};

class SPARKLE_API SEvent
{
public:
	SEvent(const SEventType& type);
	virtual ~SEvent();
	SEventType getEventType()const;
private:
	SEventType type_;
};

#endif