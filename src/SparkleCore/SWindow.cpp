#include "SWindow.h"


SWindow::SWindow(const SWindowConf& conf)
	:conf_(conf)
{

}

SWindow::~SWindow()
{

}

SWindowConf SWindow::getConf() const
{
	return conf_;
}

void SWindow::resize(const SSize2D& size)
{
	conf_.wndSize = size;
}

void SWindow::runOnce()
{

}
