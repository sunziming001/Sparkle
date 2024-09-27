#ifndef SLOGGABLE_H
#define SLOGGABLE_H

#include "SConfig.h"
#include "SString.h"
#include "SSharedPtr.h"

class SPARKLE_API SLoggable
{
public:
	virtual SStringPtr toLogString()const = 0;
};


#endif
