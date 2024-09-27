#ifndef SCOREAPPLICATION_H
#define SCOREAPPLICATION_H


#include "SConfig.h"
#include "SWindow.h"
#include "SSharedPtr.h"
#include "SEvent.h"
#include "SActiveEvent.h"
#include "SKeyboardEvent.h"


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
	virtual void onKeyboardEvent(SSharedPtr<SKeyboardEvent> e);
private:
	static SCoreApplication* instance;
private:
	DECLARE_INNER_DATA(d_)
};


#endif