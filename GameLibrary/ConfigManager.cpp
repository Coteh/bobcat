#include "ConfigManager.h"
#include <rapidjson\rapidjson.h>
#include <rapidjson\stringbuffer.h>
#include <rapidjson\prettywriter.h>

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
* Read a config file from specified filename.
*/
void ConfigManager::readConfigFile(const char* _fileName){
	std::string fileContents = fileReader.readFromFileAsString(_fileName);
	document.Parse(fileContents.c_str());
	if (document.HasParseError()){
		logManager->writeLog(LogLevel::LOG_ERROR, "Could not read config file " + std::string(_fileName));
		return; //parse error
	}
	logManager->writeLog(LogLevel::LOG_INFO, "Config file " + std::string(_fileName) + " read succesfully");
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

void ConfigManager::getWindowSettings(const char* &_name, int &_width, int &_height){
	if (!document.HasMember(CFG_KEY_WINDOW)){
		logManager->writeLog(LogLevel::LOG_ERROR, "Could not retrive window settings from config file.");
		return; //exit since window key does not have a member
	}
	Value& val = document[CFG_KEY_WINDOW];
	if (val.HasMember("title")){
		_name = val["title"].GetString();
	}
	if (val.HasMember("width")){
		_width = val["width"].GetInt();
	}
	if (val.HasMember("height")){
		_height = val["height"].GetInt();
	}
}