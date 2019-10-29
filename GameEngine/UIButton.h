#pragma once
// @author luc tran canh
// This is a simple game engine 
// for training purposes.
// Any question, please redirect to luc.trancanh@gameloft.com

#define MAX_BUFFER 255
namespace gamerize
{
	class UIButton
	{
	public:
		UIButton(const char * imgNormalPath, const char * imgPressedPath);
		UIButton(const char * imgNormalPath, const char * imgPressedPath, Vector2 posButton);
		void SetPositionButton(Vector2 posButton);
		~UIButton();
		
		Image *GetImageButton();
		void Update();
		//bool IsPressedButton();
		Vector2 GetPositionButton();
		unsigned int GetWidth();
		unsigned int GetHeight();
		void SetOnClickCallBack(void (*action)());
	private:
		Image *imageNormal;
		Image *imagePressed;
		Vector2 posButton;
		bool isPreessed;
		bool isPressing;
		void CreateButton(const char * imgNormalPath, const char * imgPressedPath);
		void UpdateStateButton();
		void (*onClickButton)();

	};

};