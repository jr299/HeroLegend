#include "GameEngine.h"

#ifdef WIN32
#include <windowsx.h> 
#endif

#define WINDOW_SCALE 1.0f

namespace gamerize
{

  Device *Device::instance = NULL;

  // singleton implementation
  Device *Device::GetInstance()
  {
    if (!instance)
    {
      instance = new Device();
    }
    return instance;
  }

  void Device::DestroyInstance()
  {
    if (instance)
    {
      delete instance;
    }
  }

	Device::Device()
		:isRunning(true)
	{
		this->graphics = NULL;
	}

	Device::~Device()
	{		
    if (graphics)
    {
		  delete graphics;
    }
	}

#ifdef WIN32

	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
    Device *device = Device::GetInstance();

		float realScreenW = device->GetWidth() * WINDOW_SCALE;
		float realScreenH = device->GetHeight() * WINDOW_SCALE;
		
		float mouseX = (GET_X_LPARAM(lParam)) / WINDOW_SCALE;
		float mouseY = (GET_Y_LPARAM(lParam)) / WINDOW_SCALE;
		/*
		float mouseX = (GET_X_LPARAM(lParam) - (realScreenW / 2.0f)) / WINDOW_SCALE;
		float mouseY = ((realScreenH / 2.0f) - GET_Y_LPARAM(lParam)) / WINDOW_SCALE;
		*/
		InputManager *inputManager = InputManager::GetInstance();

		switch(message)
		{
		case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			} break;
		case WM_KEYDOWN:
			{
				inputManager->KeyEvent((unsigned char) wParam, true);
			}
			break;

		case WM_KEYUP:
			{
				inputManager->KeyEvent((unsigned char) wParam, false);
			}
			break;
		case WM_MOUSEMOVE:
			{
				inputManager->TouchEvent(1, mouseX, mouseY, TOUCH_MOVE);
				break;
			}
		case WM_LBUTTONDOWN:
			{
				inputManager->TouchEvent(1, mouseX, mouseY, TOUCH_DOWN);
				break;
			}
		case WM_LBUTTONUP:
			{
				inputManager->TouchEvent(1, mouseX, mouseY, TOUCH_UP);
				break;
			}
		}
		return DefWindowProc (hWnd, message, wParam, lParam);
	}

#endif

	// Init the device
	void Device::InitWindow(int width, int height)
	{
		this->width = width;
		this->height = height;

		Logger::Info("Device", "Init Windows (%d - %d)", width, height);

#ifdef WIN32

		windowHandler = CreateWin("Sample Game", (int) (width * WINDOW_SCALE),  (int) (height * WINDOW_SCALE));

		EGLint attribList[] =
		{
			EGL_RED_SIZE,       5,
			EGL_GREEN_SIZE,     6,
			EGL_BLUE_SIZE,      5,
			EGL_ALPHA_SIZE,     EGL_DONT_CARE,
			EGL_DEPTH_SIZE,     8,
			EGL_STENCIL_SIZE,   EGL_DONT_CARE,
			EGL_SAMPLE_BUFFERS, 0,
			EGL_NONE
		};

		EGLint numConfigs;
		EGLint majorVersion;
		EGLint minorVersion;	
		EGLConfig config;
		EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

		// Get Display
		display = eglGetDisplay(GetDC(windowHandler));

		if ( display == EGL_NO_DISPLAY )
		{
			Logger::Error("OpenGLESDevice", "Couldn't Get Display");
			return;
		}

		// Initialize EGL
		if ( !eglInitialize(display, &majorVersion, &minorVersion) )
		{
			Logger::Error("OpenGLESDevice", "Couldn't Initialize Display");
			return;
		}

		// Get configs
		if ( !eglGetConfigs(display, NULL, 0, &numConfigs) )
		{
			Logger::Error("OpenGLESDevice", "Couldn't Get Config");
			return;
		}

		// Choose config
		if ( !eglChooseConfig(display, attribList, &config, 1, &numConfigs) )
		{
			Logger::Error("OpenGLESDevice", "Couldn't Choose Config");
			return;
		}

		// Create a surface
		surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType) windowHandler, NULL);
		if ( surface == EGL_NO_SURFACE )
		{
			Logger::Error("OpenGLESDevice", "Couldn't Create Window Surface");
			return;
		}

		// Create a GL context
		context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs );

		if ( context == EGL_NO_CONTEXT )
		{
			Logger::Error("OpenGLESDevice", "Couldn't Get Context");
			return;
		}   

		// Make the context current
		if ( !eglMakeCurrent(display, surface, surface, context) )
		{
			Logger::Error("OpenGLESDevice", "Couldn't Make Current Display");
			return;
		}
#endif // if WIN32

		graphics = new Graphics(width, height);
	}


#ifdef WIN32
	//
	// Create A Window
	HWND Device::CreateWin(const char *windowName, int width, int height)
	{
		HWND windowHandler;
		WNDCLASS windowClass;
		HINSTANCE hInstance = GetModuleHandle(NULL);
		RECT windowRect = {0, 0, width, height};
		AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

		ZeroMemory(&windowClass, sizeof(WNDCLASS));

		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = WindowProc;
		windowClass.hInstance = hInstance;
		windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
		windowClass.lpszClassName = "MyGameMaker";

		if (!RegisterClass(&windowClass))
		{
			return NULL;
		}

		windowHandler = CreateWindow(
			"MyGameMaker",
			windowName,
			WS_OVERLAPPEDWINDOW,
			0,
			0,
			windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top,
			NULL,
			NULL,
			hInstance,
			NULL
			);

		ShowWindow(windowHandler, true);
		//windowClass.
		return windowHandler;
	}

#endif

	// Is the game running
	bool Device::IsRunning()
	{
        InputManager::GetInstance()->Update();
#ifdef WIN32				
		MSG msg = { 0 };
		int gotMsg = (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0);

		if ( gotMsg )
		{
			if (msg.message == WM_QUIT)
			{
				isRunning = false;
			}
			else
			{
				TranslateMessage(&msg); 
				DispatchMessage(&msg); 
			}
		}
		else
		{
			SendMessage(windowHandler, WM_PAINT, 0, 0);
		}
#endif
		GameTime::Update();
		SwapBuffer();
		return isRunning;
	}

	void Device::SwapBuffer()
	{
#ifdef WIN32
		eglSwapBuffers(display, surface);
#endif
	}

	// quit the game
	void Device::Quit()
	{
		isRunning = false;
	}

	int Device::GetWidth()
	{
		return width;
	}

	int Device::GetHeight()
	{
		return height;
	}

	// Get the game canvas
	Graphics *Device::GetGraphics()
	{
		return graphics;
	}
}