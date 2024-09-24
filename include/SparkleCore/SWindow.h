#ifndef SWINDOW_H
#define SWINDOW_H

#include "SConfig.h"
#include "SString.h"
#include "SSize.h"
#include "SSharedPtr.h"
#include "SEvent.h"

typedef struct SWindowConf
{
	SSize2D wndSize;
	SString title;
	bool isFullScreen;
	int bits;			// Number Of Bits To Use For Color(8 / 16 / 24 / 32)
}SWindowConf;

class SPARKLE_API SWindow
{
public:
	SWindow(const SWindowConf& conf);
	virtual ~SWindow();
	SWindowConf getConf()const;
	void sendEvent(SSharedPtr<SEvent> e);

	virtual void resize(const SSize2D& size);
	virtual void runOnce();
private:
	SWindowConf conf_;
};


#endif