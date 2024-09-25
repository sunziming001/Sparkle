#include "SWindow.h"
#include "SCoreApplication.h"

SWindow::SWindow(const SWindowConf& conf)
	:conf_(conf)
{
	SCoreApplication::getInstance()->registerMainWindow(this);
}

SWindow::~SWindow()
{

}

SWindowConf SWindow::getConf() const
{
	return conf_;
}

void SWindow::sendEvent(SSharedPtr<SEvent> e)
{
	SCoreApplication::getInstance()->recvEvent(e);
}

void SWindow::resize(const SSize2D& size)
{
	conf_.wndSize = size;
}

void SWindow::runOnce()
{

}
