#ifndef _SWINDOW_MS_OPENGL_H
#define _SWINDOW_MS_OPENGL_H


#include "SWindow.h"
#include <windows.h>
#include "SKeyEvent.h"

class SPARKLE_API SWindow_MS_OpenGL:public SWindow
{
public:
	SWindow_MS_OpenGL(const SWindowConf& conf);
	virtual ~SWindow_MS_OpenGL();
	virtual void resize(const SSize2D& size);
	virtual void runOnce();
private:
	void initGL();
	bool createGLWindow();
	void killGLWindow();
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	void procWindowMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void onActive(WPARAM wParam, LPARAM lParam);
	void onMouseKey(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void onKeyboardKey(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void onMouseMove(WPARAM wParam, LPARAM lParam);

	void onKeyboardKeyDown(SKeyEnum key);
	void onKeyboardKeyUp(SKeyEnum key);

	SKeyEnum getKeyboardKey(WPARAM wParam)const;
private:
	DECLARE_INNER_DATA(d_)
};


#endif
