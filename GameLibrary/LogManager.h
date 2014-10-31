#pragma once
#include <string>

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
	LogManager();
public:
	static LogManager* getInstance();
	void setDefaultLogFileName(std::string _fileName);
	~LogManager();
};

