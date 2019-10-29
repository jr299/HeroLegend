#ifndef _WINPHONE_
#include "Shader.h"
#include "Logger.h"


namespace gamerize
{
	Shader::Shader()
	{
		vertexShader = 0;
		fragmentShader = 0;
		program = 0;
	}

	Shader::~Shader()
	{
		if (program)
		{
			glDeleteProgram(program);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
		}

	}

	// Init the shader
	void Shader::Init(const char *vertexShaderSource, const char *fragmentShaderSource)
	{
		vertexShader = CompileShader(vertexShaderSource, GL_VERTEX_SHADER);
		fragmentShader = CompileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
		program = LinkProgram();
		if (program)
		{
			positionAttribute = glGetAttribLocation(program, "aPosition");
			uvAttribute = glGetAttribLocation(program, "aUV");
			textureUniform = glGetUniformLocation(program, "uTexture");
			transformMatrixUniform = glGetUniformLocation(program, "uTransformMatrix");
			colorUniform = glGetUniformLocation(program, "uColor");
			hasTextureUniform = glGetUniformLocation(program, "uHasTexture");
		}
	}

	unsigned int Shader::CompileShader(const char *source, int type)
	{
		GLint status;
		unsigned int shader = 0;

		if (source) 
		{

			shader = glCreateShader(type);
			glShaderSource(shader, 1, &source, 0);
			glCompileShader(shader);

			glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

			if (status == 0) 
			{

				GLint infoLen = 0;

				glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen );
				if ( infoLen > 1 )
				{
					char* infoLog = new char  [infoLen];


					glGetShaderInfoLog ( shader, infoLen, 0, infoLog );
					Logger::Error("Shader", "Error compiling shader:\n%s\n", infoLog );            

					delete [] infoLog;
				}

				glDeleteShader(shader);
				shader = 0;
			}
		}

		return shader;
	}

	///
	// Link the program
	unsigned int Shader::LinkProgram()
	{
		unsigned int program = 0;
		int status = 0;

		if (vertexShader && fragmentShader)
		{
			program = glCreateProgram();
			glAttachShader(program, vertexShader);
			glAttachShader(program, fragmentShader);

			glLinkProgram(program);


			glGetProgramiv(program, GL_LINK_STATUS, &status);
			
			if (status == 0) 
			{
				glDeleteProgram(program);
				program = 0;
			}
		}
		return program;
	}
}


#endif