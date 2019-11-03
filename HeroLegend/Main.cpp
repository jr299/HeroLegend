#include <GameEngine.h>
#include "AICharacter.h"
#include "SceneManager.h"
#include <stdlib.h>
#include "Define.h"
#include <string>
#include <sstream>
using namespace std;
//#include <vld.h>
/**
* The main Program
**/
int main()
{
	// Init Game 
	Device *device = Device::GetInstance();
	device->InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
	Graphics *graphics = device->GetGraphics();
	InputManager *inputManager = InputManager::GetInstance(); 

	SceneManager* scene = SceneManager::GetInstance();
	scene->Init();
	// Game Loop
	while (device->IsRunning())
	{
		// Update game status 
		// deltaTime = time of that frame
		float deltaTime = GameTime::GetFrameTime();

		TouchData *touchData = inputManager->GetTouch();
		if (touchData != NULL
			&& (touchData->state == TOUCH_UP)
			)
		{
			// handle touch
			Logger::Debug("Touch::", "Touch state: %d x: %f y: %f", touchData->state, touchData->position.x, touchData->position.y);
			scene->OnEvent(touchData);
		}
		//Update

		// Render the scene
		graphics->ClearScreen();
		graphics->SetColor(1.0f, 0.0f, 0.0f);
		graphics->DrawArc(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, RADIUS);
		graphics->DrawRect(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, BAR_WIDTH, BAR_HEIGHT);
		scene->Render();
		scene->Update(deltaTime);
    }

	//Exit Game
    InputManager::DestroyInstance();
    Device::DestroyInstance();
    return 0;
}