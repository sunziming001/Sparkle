#include "SCoreApplication.h"
#include "SSharedPtr.h"
#include "SWindow.h"
#include "SWindow_MS_OpenGL.h"
#include <iostream>
#include "SLogger.h"

struct SCoreApplication::Data
{
	int argc;
	char** argv;
	SWindow* mainWindow;
	bool keepRun;
};

SCoreApplication* SCoreApplication::instance=nullptr;


SCoreApplication::SCoreApplication(int argc, char** argv)
	:d_(new Data())
{
	SLoggerManager* logger = SLoggerManager::getInstance();
	logger->init();

	d_->argc = argc;
	d_->argv = argv;
	
	if (instance == nullptr)
	{
		instance = this;
	}
	SInfo("App") << SWS("App Inited");
}

SCoreApplication::~SCoreApplication()
{
	delete d_;
	SInfo("App") << SWS("App Destroyed");
}

void SCoreApplication::exec()
{
	SInfo("App") << SWS("App start loop...");
	d_->keepRun = true;
	while (d_->keepRun)
	{
		if (d_->mainWindow)
		{
			d_->mainWindow->runOnce();
		}
	}
}

SCoreApplication* SCoreApplication::getInstance()
{
	return instance;
}

void SCoreApplication::recvEvent(SSharedPtr<SEvent> e)
{
	//STrace("App") << e->toLogString();
	switch (e->getEventType())
	{
	case SEventType::Active:
		onActiveEvent(spk_dynamic_pointer_cast<SActiveEvent>(e));
		break;
	case SEventType::Key:
		onKeyboardEvent(spk_dynamic_pointer_cast<SKeyEvent>(e));
		break;
	default:
		break;
	}
}

void SCoreApplication::registerMainWindow(SWindow* window)
{
	if (d_->mainWindow == nullptr)
	{
		d_->mainWindow = window;
	}
	
}

void SCoreApplication::quit()
{
	d_->keepRun = false;
}

void SCoreApplication::onActiveEvent(SSharedPtr<SActiveEvent> e)
{

}

void SCoreApplication::onKeyboardEvent(SSharedPtr<SKeyEvent> e)
{

}
