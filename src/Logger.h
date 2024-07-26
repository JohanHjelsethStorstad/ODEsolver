#pragma once
#include <array>
#include <string>
#include <fstream>

namespace Logger {
	class Logger {
	private:
		std::ofstream file;
		std::string path;
		Logger(const std::string& filepath);
	public:
		friend class Loggers;
		Logger() = delete;
		inline Logger& close();
		inline Logger& open();
		~Logger();
		Logger& operator<<(const std::string& message);
	};

	enum class LogFile {
		ReadParametersFromConfig,
		PreFrameSetContext,
		PerformanceTest,
		ConfigLog,
		ODE,
		GENERALLOG,
	};

	struct LogConfig {
		LogFile file;
		std::string path;
	};

	class Loggers {
	private:
		static std::array<LogConfig, 10> loggers;
		Loggers(const Loggers&) = delete;
		Loggers& operator=(const Loggers&) = delete;
		Loggers() = default;
		~Loggers() = default;
	public:
		static Logger getLogger(LogFile file) {
			for (LogConfig& logger : loggers) {
				if (logger.file == file) {
					return Logger(logger.path);
				}
			}
			return Logger(loggers.at(0).path);
		}
	};
}