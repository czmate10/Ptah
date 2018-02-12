#pragma once
#include <string>

namespace Ptah
{
	enum LogLevel : unsigned int
	{
		DEBUG,
		INFO,
		WARN,
		ERROR,
		CRITICAL
	};

	class Logger
	{
	public:
		/**
		 * Log message with given log level
		 */
		static void Log(std::string message, LogLevel level);
		static void Debug(std::string message);
		static void Info(std::string message);
		static void Warn(std::string message);
		static void Error(std::string message);
		static void Critical(std::string message);
	};
}
