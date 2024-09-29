#ifndef _SEVENT_H
#define _SEVENT_H

#include "SConfig.h"
#include "SString.h"
#include "SLoggable.h"

enum class SPARKLE_API SEventType
{
	None,
	Active,
	Close,
	MouseMove,
	MouseButton,
	Key,
};

class SPARKLE_API SEvent:public SLoggable
{
public:
	SEvent(const SEventType& type);
	virtual ~SEvent();
	SEventType getEventType()const;
	SStringPtr toLogString()const override;
	uint32_t getId()const;

	static SStringPtr EventTypeToString(SEventType tp);
private:
	DECLARE_INNER_DATA(d_);
};

#endif