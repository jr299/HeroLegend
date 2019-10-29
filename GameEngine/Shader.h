#ifndef _WINPHONE_
#ifndef Wobble_Shader_h
#define Wobble_Shader_h
#ifdef __APPLE__
#include <OpenGLES/ES2/gl.h>
#else
#include <GLES2/gl2.h>
#endif

namespace gamerize
{
	/**
	* The shader class that handle shader
	**/
	class Shader
	{
	public:
		Shader();
		virtual ~Shader();
		virtual void Init(const char *vertexShaderSource, const char *fragmentShaderSource);

		unsigned int program;
		unsigned int positionAttribute;
		unsigned int uvAttribute;
		unsigned int textureUniform;
		unsigned int transformMatrixUniform;
		unsigned int colorUniform;
		unsigned int hasTextureUniform;
	protected:
		unsigned int fragmentShader;
		unsigned int vertexShader;

		unsigned int CompileShader(const char *source, int type);
		unsigned int LinkProgram();
	};

};
#endif
#endif