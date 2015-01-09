#pragma once
#include <string>
#include <stdio.h> //used for printf
#include "FileWriter.h"

#define COLON_SEP "> "

namespace bobcat {

	enum LogLevel{
		LOG_NONE,
		LOG_INFO,
		LOG_TRACE,
		LOG_WARN,
		LOG_ERROR
	};

	class LogManager {
	private:
		static LogManager* instance;

		std::string defaultLogFileName;

		std::string lastErrorStr;
		LogLevel lastErrorLevel;

		FileIO::IFileWriter* fileWriter;

		LogLevel writePriority;
		LogLevel printPriority;

		std::string getLogLevelString(LogLevel _logLevel);
		LogManager();
	public:
		static LogManager* getInstance();
		void setDefaultLogFileName(std::string _fileName);
		void writeLog(LogLevel _level, std::string _message);
		void printLastError();
		~LogManager();
	};

}