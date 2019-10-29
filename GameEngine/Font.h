#ifndef FONT_H_
#define FONT_H_
// @author luc tran canh
// This is a simple game engine 
// for training purposes.
// Any question, please redirect to luc.trancanh@gameloft.com

#define MAX_BUFFER 255
namespace gamerize
{
	struct CharData
	{
		float x;
		float y;
		float ox;
		float oy;
		float w;
		float h;
		int id;
	};

	class Font
	{
		public:
			Font(const char * path);
			~Font();
			void LoadFont(const char * path);
			int FindIdChar(int id);
			float GetTextWidth(const char *str);
			float GetTextHeight();
		
			CharData *m_char;
			Image *fontImage;
			char fontPathImage[MAX_BUFFER];
			int numChar;
	};

};
#endif //FONT_H_