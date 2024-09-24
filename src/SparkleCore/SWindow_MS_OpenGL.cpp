#include "SWindow_MS_OpenGL.h"

#include <windows.h>                              // Header File For Windows
#include <gl\gl.h>                                // Header File For The OpenGL32 Library
#include <gl\glu.h>                               // Header File For The GLu32 Library

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")


struct SWindow_MS_OpenGL::Data
{
	HGLRC           hRC = NULL;                           // Permanent Rendering Context
	HDC             hDC = NULL;                           // Private GDI Device Context
	HWND            hWnd = NULL;                          // Holds Our Window Handle
	HINSTANCE       hInstance = NULL;                          // Holds The Instance Of The Application

	bool    active = TRUE;        // Window Active Flag Set To TRUE By Default
	bool    fullscreen = TRUE;    // Fullscreen Flag Set To Fullscreen Mode By Default
};


SWindow_MS_OpenGL::SWindow_MS_OpenGL(const SWindowConf& conf)
	:SWindow(conf)
	,d_(new Data())
{
	createGLWindow();
}

SWindow_MS_OpenGL::~SWindow_MS_OpenGL()
{
	delete d_;
}

void SWindow_MS_OpenGL::resize(const SSize2D& size)
{
	SWindow::resize(size);

	glViewport(0, 0, size.w, size.h);                       // Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
	glLoadIdentity();                                   // Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)size.w / (GLfloat)size.h, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);                         // Select The Modelview Matrix
	glLoadIdentity();
}

void SWindow_MS_OpenGL::runOnce()
{
	MSG msg;
	if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))           // Is There A Message Waiting?
	{
		TranslateMessage(&msg);             // Translate The Message
		DispatchMessageW(&msg);              // Dispatch The Message
	}
}

void SWindow_MS_OpenGL::initGL()
{
	glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);               // Black Background
	glClearDepth(1.0f);                                 // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);                             // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Really Nice Perspective Calculations
}

bool SWindow_MS_OpenGL::createGLWindow()
{
	GLuint      PixelFormat;            // Holds The Results After Searching For A Match
	WNDCLASS    wc;                     // Windows Class Structure
	DWORD       dwExStyle;              // Window Extended Style
	DWORD       dwStyle;                // Window Style
	RECT        WindowRect;             // Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;            // Set Left Value To 0
	WindowRect.right = (long)getConf().wndSize.w;       // Set Right Value To Requested Width
	WindowRect.top = (long)0;             // Set Top Value To 0
	WindowRect.bottom = (long)getConf().wndSize.h;     // Set Bottom Value To Requested Height

	bool fullscreen = getConf().isFullScreen;          // Set The Global Fullscreen Flag

	d_->hInstance = GetModuleHandle(NULL);                // Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;   // Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)SWindow_MS_OpenGL::WndProc;                    // WndProc Handles Messages
	wc.cbClsExtra = 0;                                    // No Extra Window Data
	wc.cbWndExtra = 0;                                    // No Extra Window Data
	wc.hInstance = d_->hInstance;                            // Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);          // Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);          // Load The Arrow Pointer
	wc.hbrBackground = NULL;                                 // No Background Required For GL
	wc.lpszMenuName = NULL;                                 // We Don't Want A Menu
	wc.lpszClassName = L"OpenGL";                             // Set The Class Name

	if (!RegisterClass(&wc))                                    // Attempt To Register The Window Class
	{
		MessageBoxW(NULL, L"Failed To Register The Window Class.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                                           // Return FALSE
	}

	if (fullscreen)                                             // Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;                               // Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));   // Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);       // Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = getConf().wndSize.w;                // Selected Screen Width
		dmScreenSettings.dmPelsHeight = getConf().wndSize.h;               // Selected Screen Height
		dmScreenSettings.dmBitsPerPel = getConf().bits;                 // Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBoxW(NULL, L"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", L"NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;       // Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, L"Program Will Now Close.", L"ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;                                   // Return FALSE
			}
		}
	}

	if (fullscreen)                                             // Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;                              // Window Extended Style
		dwStyle = WS_POPUP;                                       // Windows Style
		ShowCursor(FALSE);                                      // Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;           // Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;                            // Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);     // Adjust Window To True Requested Size

	// Create The Window
	if (!(d_->hWnd = CreateWindowExW(dwExStyle,                          // Extended Style For The Window
		L"OpenGL",                           // Class Name
		getConf().title.wc_str(),                              // Window Title
		dwStyle |                           // Defined Window Style
		WS_CLIPSIBLINGS |                   // Required Window Style
		WS_CLIPCHILDREN,                    // Required Window Style
		0, 0,                               // Window Position
		WindowRect.right - WindowRect.left,   // Calculate Window Width
		WindowRect.bottom - WindowRect.top,   // Calculate Window Height
		NULL,                               // No Parent Window
		NULL,                               // No Menu
		d_->hInstance,                          // Instance
		NULL)))                             // Dont Pass Anything To WM_CREATE
	{
		killGLWindow();                             // Reset The Display
		MessageBoxW(NULL, L"Window Creation Error.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                               // Return FALSE
	}

	static  PIXELFORMATDESCRIPTOR pfd =              // pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),              // Size Of This Pixel Format Descriptor
		1,                                          // Version Number
		PFD_DRAW_TO_WINDOW |                        // Format Must Support Window
		PFD_SUPPORT_OPENGL |                        // Format Must Support OpenGL
		PFD_DOUBLEBUFFER,                           // Must Support Double Buffering
		PFD_TYPE_RGBA,                              // Request An RGBA Format
		getConf().bits,                                       // Select Our Color Depth
		0, 0, 0, 0, 0, 0,                           // Color Bits Ignored
		0,                                          // No Alpha Buffer
		0,                                          // Shift Bit Ignored
		0,                                          // No Accumulation Buffer
		0, 0, 0, 0,                                 // Accumulation Bits Ignored
		16,                                         // 16Bit Z-Buffer (Depth Buffer)  
		0,                                          // No Stencil Buffer
		0,                                          // No Auxiliary Buffer
		PFD_MAIN_PLANE,                             // Main Drawing Layer
		0,                                          // Reserved
		0, 0, 0                                     // Layer Masks Ignored
	};

	if (!(d_->hDC = GetDC(d_->hWnd)))                         // Did We Get A Device Context?
	{
		killGLWindow();                             // Reset The Display
		MessageBoxW(NULL, L"Can't Create A GL Device Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                               // Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(d_->hDC, &pfd))) // Did Windows Find A Matching Pixel Format?
	{
		killGLWindow();                             // Reset The Display
		MessageBoxW(NULL, L"Can't Find A Suitable PixelFormat.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                               // Return FALSE
	}

	if (!SetPixelFormat(d_->hDC, PixelFormat, &pfd))       // Are We Able To Set The Pixel Format?
	{
		killGLWindow();                             // Reset The Display
		MessageBoxW(NULL, L"Can't Set The PixelFormat.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                               // Return FALSE
	}

	if (!(d_->hRC = wglCreateContext(d_->hDC)))               // Are We Able To Get A Rendering Context?
	{
		killGLWindow();                             // Reset The Display
		MessageBoxW(NULL, L"Can't Create A GL Rendering Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                               // Return FALSE
	}

	if (!wglMakeCurrent(d_->hDC, d_->hRC))                    // Try To Activate The Rendering Context
	{
		killGLWindow();                             // Reset The Display
		MessageBoxW(NULL, L"Can't Activate The GL Rendering Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                               // Return FALSE
	}

	ShowWindow(d_->hWnd, SW_SHOW);                       // Show The Window
	SetForegroundWindow(d_->hWnd);                      // Slightly Higher Priority
	SetFocus(d_->hWnd);                                 // Sets Keyboard Focus To The Window
	resize(getConf().wndSize);                   // Set Up Our Perspective GL Screen

	initGL();

	return true;                                    // Success
}

void SWindow_MS_OpenGL::killGLWindow()
{
	if (getConf().isFullScreen)                                     // Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);                  // If So Switch Back To The Desktop
		ShowCursor(TRUE);                               // Show Mouse Pointer
	}

	if (d_->hRC)                                            // Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))                 // Are We Able To Release The DC And RC Contexts?
		{
			MessageBoxW(NULL, L"Release Of DC And RC Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(d_->hRC))                     // Are We Able To Delete The RC?
		{
			MessageBoxW(NULL, L"Release Rendering Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		d_->hRC = NULL;                                       // Set RC To NULL
	}

	if (d_->hDC && !ReleaseDC(d_->hWnd, d_->hDC))                    // Are We Able To Release The DC
	{
		MessageBoxW(NULL, L"Release Device Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		d_->hDC = NULL;                                       // Set DC To NULL
	}

	if (d_->hWnd && !DestroyWindow(d_->hWnd))                   // Are We Able To Destroy The Window?
	{
		MessageBoxW(NULL, L"Could Not Release hWnd.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		d_->hWnd = NULL;                                      // Set hWnd To NULL
	}

	if (!UnregisterClass(L"OpenGL", d_->hInstance))           // Are We Able To Unregister Class
	{
		MessageBoxW(NULL, L"Could Not Unregister Class.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		d_->hInstance = NULL;                                 // Set hInstance To NULL
	}
}

LRESULT CALLBACK SWindow_MS_OpenGL::WndProc(HWND hWnd, 
	UINT uMsg, 
	WPARAM wParam, 
	LPARAM lParam)
{
	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}
