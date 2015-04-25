#include "LogManager.h"

using namespace bobcat;

LogManager* LogManager::instance;

#ifdef _WIN32
const WORD LogManager::colors[] = {
	0x0F, 0x02, 0x0D, 0x0E, 0x0C
};
#endif

LogManager::LogManager() {
	fileWriter = new FileIO::FileWriter();
	printPriority = LogLevel::LOG_INFO;

#ifdef _WIN32
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hstdout, &csbi);
#endif
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
	if (_logLevel != 0){
		logLevelString += "\t";
		logLevelString += COLON_SEP;
	}
	return logLevelString;
}

void LogManager::setLogfile(std::string _filePath){
	defaultLogFilePath = _filePath;
	fileWriter->writeToFile(defaultLogFilePath, ""); //clear out the log file before we start writing to it.
}

/* Stores the error message and then writes it to the log file.
*/
void LogManager::writeLog(LogLevel _level, std::string _message){
	if (_level < writePriority) return; //only write if error level is on write priority bracket
	lastErrorStr = getLogLevelString(_level) + _message + "\n";
	lastErrorLevel = _level;
	fileWriter->appendToFile(defaultLogFilePath, lastErrorStr);
}

void LogManager::printLastError(){
	if (lastErrorLevel < printPriority)return; //only print if error level is on print priority bracket
	int charBufferSize = lastErrorStr.length() + 1;
	char* errorCharArr = new char[charBufferSize];
	errno_t errErrCode; //to see if there was an error converting the error string to char array :P
	errErrCode = strcpy_s(errorCharArr, charBufferSize, lastErrorStr.c_str());
	if (errErrCode > 0) return;
#ifdef _WIN32
	//Determining color if on Windows systems
	WORD errLogColor;
	if (lastErrorLevel > LOG_ERROR || lastErrorLevel < 0){
		errLogColor = colors[LOG_NONE];
	} else{
		errLogColor = colors[lastErrorLevel];
	}
	SetConsoleTextAttribute(hstdout, errLogColor);
#endif
	//Print the error message to console
	printf("%s", errorCharArr);
#ifdef _WIN32
	//Setting color back to normal when done
	SetConsoleTextAttribute(hstdout, csbi.wAttributes);
#endif
}