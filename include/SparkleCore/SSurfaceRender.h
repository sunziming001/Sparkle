#ifndef _SSURFACERENDER_H
#define _SSURFACERENDER_H

#include "SConfig.h"
#include "SSurface.h"

class SPARKLE_API SSurfaceRender
{
public:
	SSurfaceRender();
	virtual ~SSurfaceRender();
	void addSurface(SSurfacePtr surface);
	void removeSurface(SSurfacePtr surface);
	void renderOnce();

protected:
	virtual void onAdd(SSurfacePtr surface)=0;
	virtual void onRemove(SSurfacePtr surface)=0;
	virtual void onBeforeRenderOnce() = 0;
	virtual void onRenderSurface(SSurfacePtr surface)=0;
	virtual void onAfterRenderOnce() = 0;
private:
	DECLARE_INNER_DATA(d_);
};

typedef SSharedPtr<SSurfaceRender> SSurfaceRenderPtr;

#endif