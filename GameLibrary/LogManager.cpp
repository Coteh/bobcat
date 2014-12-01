#include "LogManager.h"

LogManager* LogManager::instance;

LogManager::LogManager() {
	fileWriter = new FileWriter();
	printPriority = LogLevel::LOG_WARN;
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
	std::string logLevelString;
	switch (_logLevel){
	case LogLevel::LOG_ERROR:
		logLevelString = "ERROR";
		break;
	case LogLevel::LOG_NONE:
		logLevelString = "";
		break;
	case LogLevel::LOG_TRACE:
		logLevelString = "TRACE";
		break;
	case LogLevel::LOG_WARN:
		logLevelString = "WARNING";
		break;
	default:
		logLevelString = "INFO";
		break;
	}
	if (_logLevel > 0){
		logLevelString += COLON_SEP;
	}
	return logLevelString;
}

void LogManager::setDefaultLogFileName(std::string _fileName){
	defaultLogFileName = _fileName;
	fileWriter->writeToFile(defaultLogFileName, ""); //clear out the log file before we start writing to it.
}

/* Stores the error message and then writes it to the log file.
*/
void LogManager::writeLog(LogLevel _level, std::string _message){
	lastErrorStr = getLogLevelString(_level) + _message + "\n";
	lastErrorLevel = _level;
	if (_level >= writePriority){ //only write if error level is on write priority bracket
		fileWriter->appendToFile(defaultLogFileName, lastErrorStr);
	}
}

void LogManager::printLastError(){
	if (lastErrorLevel < printPriority)return; //only print if error level is on print priority bracket
	int charBufferSize = lastErrorStr.length() + 1;
	char* errorCharArr = new char[charBufferSize];
	errno_t errErrCode; //to see if there was an error converting the error string to char array :P
	errErrCode = strcpy_s(errorCharArr, charBufferSize, lastErrorStr.c_str());
	if (errErrCode > 0) return;
	printf("%s", errorCharArr);
}