#ifndef GRAPHICS_H_
#define GRAPHICS_H_



namespace gamerize
{
	
	//
	// Graphics class 
	// 
	class Graphics
	{
	public:		

		static const int LEFT = 0;
		static const int HCENTER = 2;
		static const int RIGHT = 4;
		static const int TOP = 0;
		static const int VCENTER = 8;
		static const int BOTTOM = 16;
		
		// Initialize the graphics 
		Graphics(int width, int height);

		// Destroy the graphics
		virtual ~Graphics();

		// Clear the screen
		virtual void ClearScreen(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);

		// Set the color
		virtual void SetColor(float r, float g, float b, float a = 1.0f);

		// Draw a Rectangle
		virtual void DrawRect(float x, float y, float w, float h);		

		// Fill a rectangle
		virtual void FillRect(float x, float y, float w, float h);

		// Draw an arc
		virtual void DrawArc(float x, float y, float r, float start = 0.0f, float end = 360.0f);

		// Fill an arc with color.
		virtual void FillArc(float x, float y, float r, float start = 0.0f, float end = 360.0f);
		
		// Draw a line
		virtual void DrawLine(float x1, float y1, float x2, float y2);

		// Draw image 
		virtual void DrawImage(Image *image, float x, float y, int alignment = 0);
		// Draw animation 
		virtual void DrawAnimation(Animation *animation, float x, float y, int alignment = 0);
		// Draw font
		virtual void DrawTextWithFont(Font *font, float x, float y, const char *text);
		virtual void DrawTextWithFont(Font *font, float x, float y, int i);
		// Draw Button
		virtual void DrawUIButton(UIButton *button, int alignment = 0);
	private:

		// Draw Primitive
		virtual void DrawPrimitive(unsigned int primitive, void *vertexData, int start, int count);

		int width;
		int height;

		Shader shader;
		Vector4 color;

		Matrix transformMatrix;
	};

};

#endif