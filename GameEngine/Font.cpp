
#include "GameEngine.h"
#include <stdio.h>
#include <string.h>

namespace gamerize
{
	Font::Font(const char * path)
	{
		LoadFont(path);
	}

	Font::~Font()
	{
		delete fontImage;
		delete []m_char;
	}

	void Font::LoadFont(const char * path)
	{
		FILE *file = fopen(path, "rb");
		if (file == NULL)
		{
			printf("Not open file %s !", path);
			return;
		}

		char temp[MAX_BUFFER] = "";
		char pathImage[MAX_BUFFER] = "";

		fscanf(file, "%[^\n]s", &temp);
		fscanf(file, "\n");
		fscanf(file, "%[^\n]s", &temp);
		fscanf(file, "\n");
		
		fscanf(file, "page id=0 file=\"%[a-zA-Z./]s", &pathImage);
		fscanf(file, "%[^\n]s", &temp);
		fscanf(file, "\n");
		char pathTemp[MAX_BUFFER];
		
		strcpy(pathTemp, path);
		int i = strlen(pathTemp);
		while (pathTemp[i] != '/')
		{
			i--;
		}
		pathTemp[i + 1] = '\0';
		strcat(pathTemp, pathImage);

		fontImage = new Image(pathTemp);

		fscanf(file, "chars count=%d\n", &numChar);
		m_char = new CharData[numChar];

		for (int i = 0; i < numChar; i++)
		{
			float x, y, w, h, xo, yo, xa, p, ch;
			int idtex = 0;
			fscanf(file, "char id=%d x=%f y=%f width=%f height=%f xoffset=%f yoffset=%f xadvance=%f page=%f chnl=%f\n", &idtex, &x, &y, &w, &h, &xo, &yo, &xa, &p, &ch);

			m_char[i].x = x;
			m_char[i].y = y;
			m_char[i].ox = xo;
			m_char[i].oy = yo;
			m_char[i].w = w;
			m_char[i].h = h;
			m_char[i].id = idtex;
		}

		fclose(file);
	}

	int Font::FindIdChar(int id)
	{
		for (int i = 0; i < numChar; i++)
		{
			if (m_char[i].id == id) return i;
		}
		return -1;
	}

	float Font::GetTextWidth(const char *str)
	{
		float width = 0;
		for (int i = 0; i < strlen(str); i++)
		{
			int id = FindIdChar(str[i]);
			width += m_char[id].w;
			//cheat for space
			if (str[i] == ' ')
				width += m_char[1].w;
		}
		return width;
	}

	float Font::GetTextHeight()
	{
		return  m_char[1].h;
	}

};