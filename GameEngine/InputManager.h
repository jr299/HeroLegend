#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include "TouchData.h"
#include "Rect.h"

namespace gamerize
{

	// Class Input Manager
	class InputManager
	{
	public:
		static const int MAX_TOUCHES = 5;

		enum Key
		{
			KEY_FORWARD,
			KEY_BACKWARD,
			KEY_RIGHT,
			KEY_LEFT,
			KEY_UP_ARROW,
			KEY_DOWN_ARROW,
			KEY_LEFT_ARROW,
			KEY_RIGHT_ARROW,
			KEY_FIRE,
			KEY_CHANGE_EFFECT,
			KEY_START_PROFILING,
			INCREASE_CLARITY,
			DECREASE_CLARITY,
			CONTROL_KEY_COUNTS
		};

		enum MouseEventType
		{
			NONE,
			MOUSE_MOVE,
			MOUSE_DOWN,
			MOUSE_UP
		};

		static const unsigned char KEY_CODE[CONTROL_KEY_COUNTS];

		// Have key event
		virtual void KeyEvent(unsigned char keyCode, bool down);	

		// Check if key is down or not
		virtual bool IsKeyDown(Key key);

		// Check if key is pressed or not
		virtual bool IsKeyPressed(Key key);

		// Touch Event
		virtual void TouchEvent(unsigned int id, float x, float y, TouchState type);

		// Get touches Count
		virtual int GetTouchesCount();

		// Get Touches Data
		virtual TouchData **GetTouches();

		// Get touch
		virtual TouchData *GetTouch(unsigned int touchId = 1);

		// Update touch
		virtual void Update();

    // Get the instance of the Input manager
    static InputManager *GetInstance();

    // Destroy the instance
		static void DestroyInstance();
	private:

    // initialize 
		InputManager();

		// Destroy the value
		virtual ~InputManager();

    static InputManager *instance;
		// key Pressed
		unsigned int keyPressed;

		// key down
		unsigned int keyDown;

		// Touch Data
		TouchData touches[MAX_TOUCHES];

		// Touch pointers
		TouchData *touchesPointer[MAX_TOUCHES];

		// Number of touches
		int touchesCount;
	};
};

#endif