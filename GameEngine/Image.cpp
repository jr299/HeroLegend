#include "GameEngine.h"
#ifdef WIN32
#include <png.h>
#else
#include <../Library/LibPNGAndroid/png.h>
#endif
namespace gamerize
{
	// Create Image
	Image::Image(const char *filename)
	{
		textureId = 0;
		if (filename)
		{
			Load(filename);
		}		
	}

	// Destroy the image
	Image::~Image()
	{
		if (textureId)
		{
			glDeleteTextures(1, &textureId);
		}
	}

	// Get texture id
	unsigned int Image::GetTextureId()
	{
		return textureId;
	}


	// get channels count
	unsigned int Image::GetChannelsCount()
	{
		return channelsCount;
	}

	// get Image Width
	unsigned int Image::GetWidth()
	{
		return width;
	}

	// Get image height
	unsigned int Image::GetHeight()
	{
		return height;
	}

	// Get texture width
	unsigned int Image::GetTextureWidth()
	{
		return textureWidth;
	}

	// get texture height
	unsigned int Image::GetTextureHeight()
	{
		return textureHeight;
	}

	// Load image from file
	void Image::Load(const char *filename)
	{
		FILE *fp = fopen(filename, "rb");
		char *data = NULL;

		if (fp)
		{
			png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
			png_infop infoPtr = png_create_info_struct(pngPtr);

			png_init_io(pngPtr, fp);
			png_read_info(pngPtr, infoPtr);

			width = png_get_image_width(pngPtr, infoPtr);
			height = png_get_image_height(pngPtr, infoPtr);
            
      Logger::Info("PNGImageLoader", "Reading File '%s' (%d x %d)", filename, width, height);
			
			textureWidth = FindNearestPowerOf2(width);
			textureHeight = FindNearestPowerOf2(height);

			//bits per CHANNEL! note: not per pixel!
			png_uint_32 bitdepth   = png_get_bit_depth(pngPtr, infoPtr);

			//Number of channels
			channelsCount   = png_get_channels(pngPtr, infoPtr);

			//Color type. (RGB, RGBA, Luminance, luminance alpha... palette... etc)
			png_uint_32 color_type = png_get_color_type(pngPtr, infoPtr);

			switch (color_type) 
			{
				case PNG_COLOR_TYPE_PALETTE:
					png_set_palette_to_rgb(pngPtr);        
					channelsCount = 3;           
					break;
			}

			/*if the image has a transperancy set.. convert it to a full Alpha channel..*/
			if (png_get_valid(pngPtr, infoPtr, PNG_INFO_tRNS)) 
			{
				png_set_tRNS_to_alpha(pngPtr);
				channelsCount += 1;
			}

			//We don't support 16 bit precision.. so if the image Has 16 bits per channel
			//precision... round it down to 8.
			if (bitdepth == 16)
			{
				png_set_strip_16(pngPtr);
			}

			data = new char[textureWidth * textureHeight * bitdepth * channelsCount >> 3];

			const unsigned int stride = textureWidth * bitdepth * channelsCount >> 3;
			png_bytep* rowPtrs = new png_bytep[height];

			for (unsigned int i = 0; i < height; i++) 
			{
				unsigned q = (i) * stride;
				rowPtrs[i] = (png_bytep) data + q;
			}   

			png_read_image(pngPtr, rowPtrs);

			delete [] rowPtrs;

			png_destroy_read_struct(&pngPtr, &infoPtr, NULL);

		}

		int format = channelsCount == 3 ? GL_RGB : GL_RGBA;
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, format, textureWidth, textureHeight, 0, format, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);

		delete []data;

	}

	// Get texture coordinate of a point
	Vector2 Image::GetTextureCoord(float x, float y)
	{
		return Vector2(x * 1.0f / textureWidth, y * 1.0f / textureHeight);
	}

	//
	// Find the nearest value
	//
	unsigned int Image::FindNearestPowerOf2(unsigned int value)
	{
		unsigned int result = 1;
		while (result < value)
		{
			result <<= 1;
		}
		return result;
	}

}