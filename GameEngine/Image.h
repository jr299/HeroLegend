#ifndef IMAGE_H_
#define IMAGE_H_


namespace gamerize
{
	/**
	 *
	 **/
	class Image
	{
	public:
		// Create Image
		Image(const char *filename = 0);

		// Destroy the image
		virtual ~Image();

		// Get texture id
		virtual unsigned int GetTextureId();

		// get Image channel count
		virtual unsigned int GetChannelsCount();

		// get Image Width
		virtual unsigned int GetWidth();

		// Get image height
		virtual unsigned int GetHeight();

		// Get texture width
		virtual unsigned int GetTextureWidth();

		// get texture height
		virtual unsigned int GetTextureHeight();

		// Load image from file
		virtual void Load(const char *filename);

		// Get texture coordinate of a point
		virtual Vector2 GetTextureCoord(float x, float y);
		
	private:

		virtual unsigned int FindNearestPowerOf2(unsigned int value);
		// bits per pixel
		unsigned int channelsCount;
		// texture id
		unsigned int textureId;
		// image width
		unsigned int width;
		// image height
		unsigned int height;
		// texture width
		unsigned int textureWidth;
		// texture height
		unsigned int textureHeight;
	};

};

#endif