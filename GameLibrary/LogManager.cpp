#include "LogManager.h"


LogManager::LogManager() {
}


LogManager::~LogManager() {
}

LogManager* LogManager::getInstance(){
	if (!instance){
		instance = new LogManager();
	}
	return instance;
}

void LogManager::setDefaultLogFileName(std::string _fileName){
	defaultLogFileName = _fileName;
}