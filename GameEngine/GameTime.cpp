#include "GameTime.h"
#ifdef WIN32
#include <windows.h>
#else
#include "ctime"
#endif

namespace gamerize
{

	float GameTime::frameTime = 0.0f;
	float GameTime::gameTime = 0.0f;
	long GameTime::lastTime = 0L;

	// get the frame time
	float GameTime::GetFrameTime()
	{
		return frameTime > 1.0f ? 0.1f : frameTime;
	}

	// get game time
	float GameTime::GetGameTime()
	{
		return gameTime;
	}

	// tick tox
	void GameTime::Tick(float time)
	{
		frameTime = time;
		gameTime += time;
	}

	void GameTime::Update()
	{
		long newTime = 0;
#ifdef WIN32
		newTime = GetTickCount();
#else
		timespec  now;
		newTime = lastTime;
		clock_gettime(CLOCK_MONOTONIC, &now);
		newTime = now.tv_sec * 1000.0F + (double)now.tv_nsec / 1e6;

#endif
		GameTime::Tick((newTime - lastTime) * 0.001f);
		lastTime = newTime;
	}
};