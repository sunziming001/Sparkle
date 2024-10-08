#ifndef _SSURFACE_RENDER_OPEN_GL_H
#define _SSURFACE_RENDER_OPEN_GL_H

#include "SConfig.h"
#include "SSurfaceRender.h"



class SSurfaceRender_OpenGL :public SSurfaceRender
{
public:
	SSurfaceRender_OpenGL();
	virtual ~SSurfaceRender_OpenGL();
protected:
	void onAdd(SSurfacePtr surface)override;
	void onRemove(SSurfacePtr surface)override;
	void onBeforeRenderOnce()override;
	void onRenderSurface(SSurfacePtr surface)override;
	void onAfterRenderOnce()override;
private:
	void initShader();
private:
	DECLARE_INNER_DATA(d_);
};

#endif