#include "ConfigHolder.h"
#include <iostream>
#include <sstream>

using namespace bobcat;

//TO DO
//Add a writer to the ConfigHolder.
//Create a default config file if there isn't one in the folder.
//Add error handling.

ConfigHolder::ConfigHolder() {
	//Getting LogManager singleton
	logManager = LogManager::getInstance();
}

ConfigHolder::~ConfigHolder() {
}

void ConfigHolder::readConfigFile(const char* _filePath){
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

bool ConfigHolder::hasSetting(std::string _settingName) {
	return document.HasMember(_settingName.c_str());
}

bool ConfigHolder::getJSONValue(std::string _key, rapidjson::Value &_val){
	//Check if document had a parse error
	if (document.HasParseError()) return false;
	//Create rapidjson value pointer
	rapidjson::Value *currJsonObj = &document;
	//Break up the key string parameter with the "." delimiter
	std::istringstream iss(_key);
	std::vector<std::string> keyPartsVec;
	while (std::getline(iss, _key, '.')){
		keyPartsVec.push_back(_key);
	}
	//Create an object depth count to indicate how deep in the json tree we are
	int objectDepth = 0;
	//Iterate through the json members, starting from root
	for (rapidjson::Value::MemberIterator memberItr = currJsonObj->MemberBegin(); memberItr != currJsonObj->MemberEnd(); ++memberItr) {
		//Check if the current key we are iterating is the one we are currently on in our list.
		//If it is, then check if it's an Object, and then switch over to this key.
		if (memberItr->name.GetString() == keyPartsVec[objectDepth] && memberItr->value.IsObject()){
			currJsonObj = &memberItr->value; //switch the current json object observed
			memberItr = currJsonObj->MemberBegin() - 1; //reset the incrementation (and minus one because it'll be iterated next loop)
			objectDepth++; //we just decended into the json tree hierarchy
		}
		//If we are on the last key, the one that will have the value we want
		if (objectDepth == keyPartsVec.size() - 1) {
			memberItr = currJsonObj->FindMember(keyPartsVec[objectDepth].c_str());
			//Did we find a valid member?
			if (memberItr != currJsonObj->MemberEnd()){
				_val = memberItr->value; //return the value we found to the user
				return true;
			} else{
				return false; //it's not here, just give up
			}
		}
	}

	return false;
}

std::string ConfigHolder::getString(std::string _key){
	rapidjson::Value val;

	if (getJSONValue(_key, val) && val.IsString()){
		return val.GetString();
	}

	return "";
}

int ConfigHolder::getInt(std::string _key){
	rapidjson::Value val;

	if (getJSONValue(_key, val) && val.IsInt()){
		return val.GetInt();
	}

	return NULL;
}

float ConfigHolder::getFloat(std::string _key){
	rapidjson::Value val;

	if (getJSONValue(_key, val) && val.IsDouble()){
		return (float)val.GetDouble();
	}

	return NULL;
}

double ConfigHolder::getDouble(std::string _key){
	rapidjson::Value val;

	if (getJSONValue(_key, val) && val.IsDouble()){
		return val.GetDouble();
	}

	return NULL;
}

bool ConfigHolder::getBool(std::string _key){
	rapidjson::Value val;

	if (getJSONValue(_key, val) && val.IsBool()){
		return val.GetBool();
	}

	return NULL;
}

int* ConfigHolder::getIntArray(std::string _key) {
	rapidjson::Value val;

	if (getJSONValue(_key, val) && val.IsArray()){
		rapidjson::SizeType arrSize = val.Size();
		int *arrToReturn = new int[arrSize];
		for (rapidjson::SizeType i = 0; i < arrSize; i++){
			arrToReturn[i] = val[i].GetInt();
		}
		return arrToReturn;
	}

	return nullptr;
}

std::string* ConfigHolder::getStringArray(std::string _key) {
	rapidjson::Value val;

	if (getJSONValue(_key, val) && val.IsArray()){
		rapidjson::SizeType arrSize = val.Size();
		std::string *arrToReturn = new std::string[arrSize];
		for (rapidjson::SizeType i = 0; i < arrSize; i++){
			arrToReturn[i] = val[i].GetString();
		}
		return arrToReturn;
	}

	return nullptr;
}