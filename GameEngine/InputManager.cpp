#include "InputManager.h"
#include "Logger.h"
#include <memory.h>
#include <string.h>

namespace gamerize
{

	const unsigned char InputManager::KEY_CODE[CONTROL_KEY_COUNTS] = {'W', 'S', 'A', 'D', 38, 40, 37, 39, ' ', 'P', 188, 190};

  InputManager *InputManager::instance = NULL;

  
  InputManager *InputManager::GetInstance()
  {
    if (!instance)
    {
      instance = new InputManager();
    }
    return instance;
  }

  void InputManager::DestroyInstance()
  {
    if (instance)
    {
      delete instance;
    }
  }

	// 
	// Initialize the Input Manager
	InputManager::InputManager()
	{
		keyPressed = 0;
		keyDown = 0;
		touchesCount = 0;
		memset(touches, 0, sizeof(touches));
	}

	// Destroy the value
	InputManager::~InputManager()
	{
	}

	// Have key event
	void InputManager::KeyEvent(unsigned char keyCode, bool down)
	{
		for (int i = 0; i < CONTROL_KEY_COUNTS; i++)
		{
			if (keyCode == InputManager::KEY_CODE[i])
			{
				if (down)
				{
					keyPressed |= (1 << i);
					keyDown |= (1 << i);
				}
				else
				{
					keyPressed &= ~(1 << i);
					keyDown &= ~(1 << i);
				}
			}
		}
	}

	// Handle touch event
	void InputManager::TouchEvent(unsigned int touchId, float x, float y, gamerize::TouchState state)
	{
		//Logger::Info("TouchEvent", "Touch event %d %d %f %f", touchId, state, x, y);
		if (state == TOUCH_DOWN)
		{
			bool oldTouch = false;

			for (int i = 0; i < MAX_TOUCHES; i++)
			{
				if (touches[i].touchId == touchId)
				{
					oldTouch = true;
				}
			}

			if (!oldTouch)
			{
				for (int i = 0; i < MAX_TOUCHES; i++)
				{
					if (!touches[i].touchId)
					{
						touches[i].touchId = touchId;
						touches[i].position.x = x;
						touches[i].position.y = y;
						touches[i].originalPoint.x = x;
						touches[i].originalPoint.y = y;
						touches[i].state = state;
						touchesCount++;
						break;
					}
				}
			}
		}
		else if (state == TOUCH_MOVE)
		{
			for (int  i = 0; i < MAX_TOUCHES; i++)
			{
				if (touches[i].touchId == touchId) {
					touches[i].position.x = x;
					touches[i].position.y = y;
					touches[i].state = TOUCH_MOVE;
					break;
				}
			}
		}
		else
		{
			for (int  i = 0; i < MAX_TOUCHES; i++)
			{
				if (touches[i].touchId == touchId) {
					touches[i].position.x = x;
					touches[i].position.y = y;
					touches[i].state = TOUCH_UP;
					break;
				}
			}
		}
	}

	// Update touches handle
	void InputManager::Update()
	{
		// first find the touch
		for (int i = 0; i < MAX_TOUCHES; i++)
		{
			if (touches[i].touchId &&  touches[i].state == TOUCH_UP)
			{
				touches[i].touchId = 0;
				touchesCount--;
			}
		}
	}

	// Get touch count
	int InputManager::GetTouchesCount()
	{
		return touchesCount;
	}

	// Get touches
	TouchData *InputManager::GetTouch(unsigned int touchId)
	{
		TouchData *result = 0;
		for (int i = 0; i < MAX_TOUCHES; i++)
		{
			if (touches[i].touchId == touchId)
			{
				result = &touches[i];
				break;
			}
		}
		return result;
	}

	// Get pointers to all touches
	TouchData **InputManager::GetTouches()
	{
		int count = 0;
		for (int i = 0; i < MAX_TOUCHES; i++)
		{
			if (touches[i].touchId)
			{
				touchesPointer[count++] = &touches[i];
			}
		}

		return touchesPointer;
	}

	// Check if key is down or not
	bool InputManager::IsKeyDown(Key key)
	{
		return (keyDown & (1 << key)) != 0;
	}

	// Check if key is down or not
	bool InputManager::IsKeyPressed(Key key)
	{
		bool result = (keyPressed & (1 << key)) != 0;
		keyPressed &= ~(1 << key);
		return result;
	}

};