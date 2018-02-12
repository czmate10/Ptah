#include "Logger.h"
#include <iostream>

void Ptah::Logger::Log(std::string message, LogLevel level)
{
	std::cout << message << std::endl;
}

void Ptah::Logger::Debug(std::string message)
{
	Ptah::Logger::Log(message, LogLevel::DEBUG);
}

void Ptah::Logger::Info(std::string message)
{
	Ptah::Logger::Log(message, LogLevel::INFO);
}

void Ptah::Logger::Warn(std::string message)
{
	Ptah::Logger::Log(message, LogLevel::WARN);
}

void Ptah::Logger::Error(std::string message)
{
	Ptah::Logger::Log(message, LogLevel::ERROR);
}

void Ptah::Logger::Critical(std::string message)
{
	Ptah::Logger::Log(message, LogLevel::CRITICAL);
}