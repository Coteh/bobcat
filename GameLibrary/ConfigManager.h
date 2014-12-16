#pragma once
#include "LogManager.h"
#include "FileReader.h"
#include <rapidjson\document.h>

#define CFG_KEY_WINDOW "window"

class ConfigManager {
private:
	static ConfigManager* instance;
	LogManager* logManager;
	FileWriter fileWriter;
	FileReader fileReader;
	rapidjson::Document document;
	ConfigManager();
public:
	static ConfigManager* getInstance();
	~ConfigManager();
	void readConfigFile(const char* _fileName);
	/*bool writeConfigFile(const char* _fileName);*/
	void getWindowSettings(const char* &_name, int &_width, int &_height);
};

