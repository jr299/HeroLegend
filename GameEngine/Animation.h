#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <list>
namespace gamerize
{
	/**
	 *
	 **/
	class Animation
	{
	public:
		enum STATE_ANIM
		{
			PLAYING,
			PAUSED,
			STOPED
		};
		// Create Animation
		Animation();
		Animation(std::list<Image*> imageList);
		Animation(std::list<Image*> imageList, float frameSpeed);
		//copyconstrucstor
		Animation(Animation *anim);
		Animation(Animation &anim);
		~Animation();

		float GetFrameSpeed();
		void SetFrameSpeed(float frameSpeed);
		void SetLoop(unsigned int numLoop);
		void SetAnimation(std::list<Image*> imageList);
		void SetAnimation(std::list<Image*> imageList, float frameSpeed);
		std::list<Image*> GetListFrame();
		void AddFrame(Image *image);
		Image * GetFrame();
		unsigned int GetWidth();
		unsigned int GetHeight();

		void SetEnableAnimation(bool isEnable);
		bool IsEnableAnimation();
		void PlayAnimation(unsigned int numLoop = 0);
		void StopAnimation();
		void PauseAnimation();
		void RestoreAnimation();
		
	private:

		std::list<Image*> imageList;
		float frameSpeed;
		unsigned int frameIndex = 0;
		int frameCount = 0;
		unsigned int numLoop;
		unsigned int loopCount;
		bool isEndedAnim = false;
		bool isEnableAnim;
		int stateAnim;
	};
};

#endif