#ifndef DEVICE_H_
#define DEVICE_H_

#ifdef OPENGLES2
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#endif

namespace gamerize
{  
	//
	// The device
	//
	class Device
	{
	public:	

		// Init the device
		virtual void InitWindow(int width, int height);

		// Is the device running
		virtual bool IsRunning();

		// Swap the buffer
		virtual void SwapBuffer();

		// quit the game
		virtual void Quit();

		// 
		virtual int GetWidth();

		// get height of this
		virtual int GetHeight();	

		// Get the game canvas
		virtual Graphics *GetGraphics();

    static Device* GetInstance();

    static void DestroyInstance();
  private:

    // Create the device
		Device();

    // Destroy the device
		virtual ~Device();

    static Device *instance;


		// is running
		bool isRunning;

		Graphics *graphics;

		int width, height;

#if WIN32	
		EGLSurface surface;
		EGLDisplay display;
		EGLContext context;
		HWND windowHandler;
		HWND CreateWin(const char *windowName, int width, int height);
#endif

	};
}
#endif