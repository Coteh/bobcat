#include "LogManager.h"

LogManager* LogManager::instance;

LogManager::LogManager() {
	fileWriter = new FileWriter();
}

LogManager::~LogManager() {
}

LogManager* LogManager::getInstance(){
	if (!instance){
		instance = new LogManager();
	}
	return instance;
}

std::string LogManager::getLogLevelString(LogLevel _logLevel){
	switch (_logLevel){
	case LogLevel::LOG_ERROR:
		return "ERROR: ";
		break;
	case LogLevel::LOG_NONE:
		return "";
		break;
	case LogLevel::LOG_TRACE:
		return "TRACE: ";
		break;
	case LogLevel::LOG_WARN:
		return "WARNING: ";
		break;
	}
	return "INFO: ";
}

void LogManager::setDefaultLogFileName(std::string _fileName){
	defaultLogFileName = _fileName;
	fileWriter->writeToFile(defaultLogFileName, ""); //clear out the log file before we start writing to it.
}

void LogManager::writeLog(LogLevel _level, std::string _message){
	fileWriter->appendToFile(defaultLogFileName, getLogLevelString(_level) + _message + "\n");
}