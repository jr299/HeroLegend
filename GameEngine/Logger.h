#ifndef LOGGER_H_
#define LOGGER_H_

namespace gamerize
{

	class Logger
	{
	public:
		enum DebugLevel { INFO_LEVEL, DEBUG_LEVEL, ERROR_LEVEL, NONE};

		// Set
		static void SetDebugLevel(DebugLevel debugLevel);

		static void Info(const char *tag, const char *message, ...);
		static void Debug(const char *tag, const char *message, ...);
		static void Error(const char *tag, const char *message, ...);	
	private:
		static DebugLevel debugLevel;
		static void Out(Logger::DebugLevel level, const char *tag, const char *message);
		static const char* LEVEL_LABEL[NONE];
	};

};
#endif