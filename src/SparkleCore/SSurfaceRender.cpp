#include "SSurfaceRender.h"
#include <set>

struct SSurfaceRender::Data
{
	std::set<SSurfacePtr> surfaceSet;
};

SSurfaceRender::SSurfaceRender()
	:d_(new Data())
{

}

SSurfaceRender::~SSurfaceRender()
{
	delete d_;
}

void SSurfaceRender::addSurface(SSurfacePtr surface)
{
	onAdd(surface);
	d_->surfaceSet.insert(surface);
}

void SSurfaceRender::removeSurface(SSurfacePtr surface)
{
	d_->surfaceSet.erase(surface);
	onRemove(surface);
}

void SSurfaceRender::renderOnce()
{
	onBeforeRenderOnce();
	for (auto iter = d_->surfaceSet.begin();
		iter != d_->surfaceSet.end();
		iter++)
	{
		onRenderSurface(*iter);
	}
	onAfterRenderOnce();
}

