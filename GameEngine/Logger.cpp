#include "Logger.h"
#include <stdarg.h>
#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#endif

#ifdef __ANDROID__
#include <android/log.h>
#endif

namespace gamerize
{

// default debug level equals to INFO
Logger::DebugLevel Logger::debugLevel = Logger::INFO_LEVEL;

const char* Logger::LEVEL_LABEL[Logger::NONE] = {"INFO ", "DEBUG", "ERROR"};

//
// Set The debug level of this project
// 
void Logger::SetDebugLevel(DebugLevel debugLevel)
{
	Logger::debugLevel = debugLevel;
}


//
// Out put the message at INFO level
//
void Logger::Info(const char *tag, const char *message, ...)
{
	char buffer[2048];
	va_list currentList;
	va_start(currentList, message);
	vsprintf(buffer, message, currentList);
	Logger::Out(Logger::INFO_LEVEL, tag, buffer);
	va_end(currentList);
}

//
// Out put the message at DEBUG level
//
void Logger::Debug(const char *tag, const char *message, ...)
{
	char buffer[2048];
	va_list currentList;
	va_start(currentList, message);
	vsprintf(buffer, message, currentList);
	Logger::Out(Logger::DEBUG_LEVEL, tag, buffer);
	va_end(currentList);
}

//
// Out put the message at DEBUG level
//
void Logger::Error(const char *tag, const char *message, ...)
{
	char buffer[2048];
	va_list currentList;
	va_start(currentList, message);
	vsprintf(buffer, message, currentList);
	Logger::Out(Logger::ERROR_LEVEL, tag, buffer);
	va_end(currentList);
}

//
// Out put the message
//
void Logger::Out(Logger::DebugLevel level, const char *tag, const char *message)
{
	if (level >= Logger::debugLevel)
	{
		char buffer[2048];
		sprintf(buffer, "%s: [%s] %s\n", Logger::LEVEL_LABEL[level], tag, message);

		printf("%s", buffer);

#ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_INFO, tag, "%s", buffer);
#endif

#if WIN32
		OutputDebugString(buffer);
#endif
	}
}

}