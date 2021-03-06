#include "ConfigManager.h"
#include <rapidjson\rapidjson.h>
#include <rapidjson\stringbuffer.h>
#include <rapidjson\prettywriter.h>

using namespace bobcat;
using namespace rapidjson;

ConfigManager* ConfigManager::instance;

ConfigManager::ConfigManager() {
	logManager = LogManager::getInstance();
}

ConfigManager::~ConfigManager() {
}

ConfigManager* ConfigManager::getInstance(){
	if (!instance){
		instance = new ConfigManager();
	}
	return instance;
}

/**
* Read a config file from specified file path.
*/
void ConfigManager::readConfigFile(const char* _filePath){
	std::string fileContents = fileReader.readFromFileAsString(_filePath);
	document.Parse(fileContents.c_str());
	if (document.HasParseError()){
		logManager->log(LogLevel::LOG_ERROR, "Could not read config file " + std::string(_filePath));
		return; //parse error
	}
	logManager->log(LogLevel::LOG_INFO, "Config file " + std::string(_filePath) + " read succesfully");
}

//bool ConfigManager::writeConfigFile(const char* _fileName){
//	rapidjson::StringBuffer buffer;
//	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
//	document.Accept(writer);
//	writer.StartObject();
//	writer.String("newTest1");
//	writer.String("newTest2");
//	writer.String("newTest3");
//	writer.String("newTest4");
//	writer.EndObject();
//	fileWriter.writeToFile("engine.config", buffer.GetString());
//	return true;
//}

bool ConfigManager::getWindowSettings(WindowSettings* _windowSettings){
	if (document.HasParseError() || !document.HasMember(CFG_KEY_WINDOW)){
		logManager->log(LogLevel::LOG_ERROR, "Could not retrive window settings from config file.");
		return false; //exit since window key does not have a member
	}
	Value& val = document[CFG_KEY_WINDOW];
	if (val.HasMember("title")){
		_windowSettings->windowName = val["title"].GetString();
	}
	if (val.HasMember("width")){
		_windowSettings->windowWidth = val["width"].GetInt();
	}
	if (val.HasMember("height")){
		_windowSettings->windowHeight = val["height"].GetInt();
	}
	return true;
}

bool ConfigManager::getAssetLoadPaths(AssetPaths* _assetPaths) {
	if (document.HasParseError() || !document.HasMember(CFG_KEY_ASSETPATHS)){
		logManager->log(LogLevel::LOG_ERROR, "Could not retrive asset load paths from config file.");
		return false; //exit since window key does not have a member
	}
	Value& val = document[CFG_KEY_ASSETPATHS];
	if (val.HasMember("models")){
		_assetPaths->modelPath = val["models"].GetString();
	}
	if (val.HasMember("textures")){
		_assetPaths->texPath = val["textures"].GetString();
	}
	if (val.HasMember("shaders")){
		_assetPaths->shadersPath = val["shaders"].GetString();
	}
	return true;
}

bool ConfigManager::getLogSettings(LogSettings* _logSettings){
	if (document.HasParseError() || !document.HasMember(CFG_KEY_LOGSETTINGS)){
		logManager->log(LogLevel::LOG_ERROR, "Could not retrive log settings from config file.");
		return false;
	}
	Value& val = document[CFG_KEY_LOGSETTINGS];
	if (val.HasMember("write-priority-level")){
		_logSettings->writePriority = val["write-priority-level"].GetInt();
	}
	if (val.HasMember("print-priority-level")){
		_logSettings->printPriority = val["print-priority-level"].GetInt();
	}
	return true;
}