#include "SCoreApplication.h"
#include "SSharedPtr.h"
#include "SWindow.h"
#include "SWindow_MS_OpenGL.h"

struct SCoreApplication::Data
{
	int argc;
	char** argv;
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
	
}

SCoreApplication* SCoreApplication::getInstance()
{
	return instance;
}

void SCoreApplication::recvEvent(SSharedPtr<SEvent> e)
{
	switch (e->getEventType())
	{
	case SEventType::Active:
		onActiveEvent(spk_dynamic_pointer_cast<SActiveEvent>(e));
		break;
	default:
		break;
	}
}

void SCoreApplication::onActiveEvent(SSharedPtr<SActiveEvent> e)
{

}
