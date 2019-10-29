#include "GameEngine.h"

namespace gamerize
{
	Animation::Animation()
	{
		this->frameSpeed = 1;
		this->numLoop = 0;
		this->isEnableAnim = false;
		stateAnim = STOPED;
		loopCount = 0;
	}

	Animation::Animation(std::list<Image*> imageList)
	{
		this->imageList = imageList;
		this->frameSpeed = 1;
		this->numLoop = true;
		this->isEnableAnim = false;
		stateAnim = STOPED;
		loopCount = 0;
	}

	Animation::Animation(std::list<Image*> imageList, float frameSpeed)
	{
		this->imageList = imageList;
		this->frameSpeed = frameSpeed;
		this->numLoop = 0;
		this->isEnableAnim = false;
		stateAnim = STOPED;
		loopCount = 0;
	}

	//copyconstrucstor
	Animation::Animation(Animation *anim)
	{
		std::list<Image*>::iterator item;
		item = anim->imageList.begin();
		for (item; item != anim->imageList.end(); ++item)
		{
			Image *image = (*item);
			this->imageList.push_back(image);
		}
		this->frameSpeed = anim->frameSpeed;
		this->numLoop = anim->numLoop;
		this->isEnableAnim = anim->isEnableAnim;
		stateAnim = anim->stateAnim;
		loopCount = 0;
	}

	Animation::Animation(Animation &anim)
	{
		std::list<Image*>::iterator item;
		item = anim.imageList.begin();
		for (item; item != anim.imageList.end(); ++item)
		{
			Image *image = (*item);
			this->imageList.push_back(image);
		}
		this->frameSpeed = anim.frameSpeed;
		this->numLoop = anim.numLoop;
		this->isEnableAnim = anim.isEnableAnim;
		stateAnim = anim.stateAnim;
		loopCount = 0;
	}

	Animation::~Animation()
	{
		std::list<Image*>::iterator item;
		item = imageList.begin();
		for (item; item != imageList.end(); ++item)
		{
			delete (*item);
		}
		imageList.clear();
	}

	float Animation::GetFrameSpeed()
	{
		return this->frameSpeed;
	}

	void Animation::SetFrameSpeed(float frameSpeed)
	{
		this->frameSpeed = frameSpeed;
	}

	void Animation::SetLoop(unsigned int numLoop)
	{
		this->numLoop = numLoop;
	}

	void Animation::SetAnimation(std::list<Image*> imageList)
	{
		this->imageList = imageList;
	}

	void Animation::SetAnimation(std::list<Image*> imageList, float frameSpeed)
	{
		this->imageList = imageList;
		this->frameSpeed = frameSpeed;
		this->numLoop = 0;
	}

	std::list<Image*> Animation::GetListFrame()
	{
		return this->imageList;
	}

	void Animation::AddFrame(Image *image)
	{
		imageList.push_back(image);
	}

	Image * Animation::GetFrame()
	{
		//float deltaTime = GameTime::GetFrameTime();
		
		

		std::list<Image*>::iterator item;
		item = imageList.begin();
		std::advance(item, frameIndex);
		
		if (stateAnim == PAUSED)
		{
			return (*item);
		}

		if (frameCount >= frameSpeed)
		{
			frameCount = 0;
			frameIndex++;
		}
		else
		{
			frameCount++;
			
		}

		if (frameIndex > imageList.size()-1)
		{
			if (loopCount <= this->numLoop || this->numLoop == 0)
			{
				frameIndex = 0;
				loopCount++;
			}
			else
			{
				frameIndex = imageList.size()-1;
				isEndedAnim = true;
				isEnableAnim = false;
			}
		}

		return (*item);
	}

	unsigned int Animation::GetWidth()
	{
		return (*imageList.begin())->GetWidth();
	}

	unsigned int Animation::GetHeight()
	{
		return (*imageList.begin())->GetHeight();
	}

	void Animation::SetEnableAnimation(bool isEnable)
	{
		this->isEnableAnim = isEnable;
	}

	bool Animation::IsEnableAnimation()
	{
		return this->isEnableAnim;
	}

	void Animation::PlayAnimation(unsigned int numLoop)
	{
		this->isEnableAnim = true;
		this->isEndedAnim = false;
		stateAnim = PLAYING;
		frameCount = 0;
		frameIndex = 0;
		this->numLoop = numLoop;
	}

	void Animation::StopAnimation()
	{
		this->isEnableAnim = false;
		this->isEndedAnim = true;
		stateAnim = STOPED;
	}

	void Animation::PauseAnimation()
	{
		stateAnim = PAUSED;
	}

	void Animation::RestoreAnimation()
	{
		stateAnim = PLAYING;
	}
}