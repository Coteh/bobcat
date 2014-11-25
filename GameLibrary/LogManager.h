#pragma once
#include <string>
#include "FileWriter.h"

using namespace FileIO;

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
	IFileWriter* fileWriter;
	std::string getLogLevelString(LogLevel _logLevel);
	LogManager();
public:
	static LogManager* getInstance();
	void setDefaultLogFileName(std::string _fileName);
	void writeLog(LogLevel _level, std::string _message);
	~LogManager();
};

