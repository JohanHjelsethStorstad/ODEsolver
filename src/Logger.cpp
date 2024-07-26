#include "Logger.h"

std::array<Logger::LogConfig, 10> Logger::Loggers::loggers = {
	{
		{LogFile::ODE, "ODE.txt"},
	}
};

Logger::Logger::Logger(const std::string& filepath) : path(filepath)
{
	this->open();
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open log file: " + filepath);
	}
}

Logger::Logger::~Logger() {
	this->close();
}

Logger::Logger& Logger::Logger::close()
{
	if (file.is_open()) {
		file.close();
	}
	return *this;
}

Logger::Logger& Logger::Logger::open() {
	if (!file.is_open()) {
		file.open("logs/" + path, std::ios_base::app);
	}
	return *this;
}

Logger::Logger& Logger::Logger::operator<<(const std::string& message)
{
	if (!file.is_open()) return *this;
	file << message;
	return *this;
}