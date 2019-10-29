#include "GameEngine.h"
namespace gamerize
{

	UIButton::UIButton(const char * imgNormalPath, const char * imgPressedPath) :UIButton(imgNormalPath, imgPressedPath, Vector2(0,0))
	{

	}

	UIButton::UIButton(const char * imgNormalPath, const char * imgPressedPath, Vector2 posButton)
	{
		isPressing = false;
		isPreessed = false;
		this->posButton = posButton;
		CreateButton(imgNormalPath, imgPressedPath);
	}

	UIButton::~UIButton()
	{
		delete imageNormal;
		delete imagePressed;
	}

	void UIButton::SetPositionButton(Vector2 posButton)
	{
		this->posButton = posButton;
	}

	Vector2 UIButton::GetPositionButton()
	{
		return this->posButton;
	}

	void UIButton::CreateButton(const char * imgNormalPath, const char * imgPressedPath)
	{
		imageNormal = new Image(imgNormalPath);
		imagePressed = new Image(imgPressedPath);
	}

	Image * UIButton::GetImageButton()
	{
		if (isPressing) return imagePressed;

		return imageNormal;
	}

	void UIButton::Update()
	{
		if (isPreessed)
		{
			isPreessed = false;
			onClickButton();
		}
		else
		{
			UpdateStateButton();
			//return false;
		}
	}

	void UIButton::UpdateStateButton()
	{
		TouchData *touchData = InputManager::GetInstance()->GetTouch();
		if (touchData != NULL && (touchData->state == TOUCH_DOWN || touchData->state == TOUCH_MOVE))
		{
			// handle touch

			if (touchData->position.x > posButton.x && touchData->position.x < posButton.x + imageNormal->GetWidth()
				&& touchData->position.y > posButton.y && touchData->position.y < posButton.y + imageNormal->GetHeight()
				)
			{
				isPressing = true;
			}
			else
			{
				isPressing = false;
			}

			//Logger::Debug("Touch::", "Touch state: %d x: %f y: %f", touchData->state, touchData->position.x, touchData->position.y);
		}
		else if (touchData != NULL && touchData->state == TOUCH_UP)
		{


			if (isPressing && !isPreessed
				&& (touchData->position.x > posButton.x && touchData->position.x < posButton.x + imageNormal->GetWidth()
				&& touchData->position.y > posButton.y && touchData->position.y < posButton.y + imageNormal->GetHeight())
				)
			{
				isPreessed = true;
			}
			isPressing = false;
		}
		else
		{
			isPressing = false;
		}
	}

	unsigned int UIButton::GetWidth()
	{
		return imageNormal->GetWidth();
	}

	unsigned int UIButton::GetHeight()
	{
		return imageNormal->GetHeight();
	}

	void UIButton::SetOnClickCallBack(void(*action)())
	{
		onClickButton = action;
	}
}