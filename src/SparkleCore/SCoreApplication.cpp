#include "SCoreApplication.h"
#include "SSharedPtr.h"
#include "SWindow.h"
#include "SWindow_MS_OpenGL.h"
#include <iostream>

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
	d_->argc = argc;
	d_->argv = argv;
	
	if (instance == nullptr)
	{
		instance = this;
	}
}

SCoreApplication::~SCoreApplication()
{
	delete d_;
}

void SCoreApplication::exec()
{
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
	std::cout<< e->toLogString()->toUtf8().data()<<std::endl;
	switch (e->getEventType())
	{
	case SEventType::Active:
		onActiveEvent(spk_dynamic_pointer_cast<SActiveEvent>(e));
		break;
	case SEventType::Keyboard:
		onKeyboardEvent(spk_dynamic_pointer_cast<SKeyboardEvent>(e));
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

void SCoreApplication::onKeyboardEvent(SSharedPtr<SKeyboardEvent> e)
{

}
