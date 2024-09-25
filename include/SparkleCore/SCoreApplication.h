#ifndef SCOREAPPLICATION_H
#define SCOREAPPLICATION_H

#include "SConfig.h"
#include "SSharedPtr.h"
#include "SEvent.h"
#include "SActiveEvent.h"
#include "SWindow.h"

class SPARKLE_API SCoreApplication
{
public:
	SCoreApplication(int argc, char** argv);
	virtual ~SCoreApplication();
	void exec();
	static SCoreApplication* getInstance();
	void recvEvent(SSharedPtr<SEvent> e);
	void registerMainWindow(SWindow* window);
	void quit();
protected:
	virtual void onActiveEvent(SSharedPtr<SActiveEvent> e);
private:
	static SCoreApplication* instance;
private:
	DECLARE_INNER_DATA(d_)
};


#endif