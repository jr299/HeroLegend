#ifndef GAME_TIME_H_
#define GAME_TIME_H_

namespace gamerize
{
  // the time of the game
  class GameTime
  {
  public:
    // get the frame time
    static float GetFrameTime();
    // get game time
    static float GetGameTime();

    // tick tox
    static void Tick(float frameTime);

	// Update a frame
	static void Update();
  private:
    static float frameTime;
    static float gameTime;

	static long lastTime;
  };
};


#endif