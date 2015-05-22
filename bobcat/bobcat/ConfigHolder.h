#pragma once
#include "LogManager.h"
#include "FileReader.h"
#include <rapidjson\document.h>

namespace bobcat {

	/**
	* A holder class that opens up a JSON configuration file and stores properties it reads from it.
	* Using the RapidJSON header-only library.
	*/
	class ConfigHolder {
	public:
		ConfigHolder();
		~ConfigHolder();

		/**
		* Read a configuration file from specified file path.
		* @param _filePath File path of the configuration file to read.
		*/
		void readConfigFile(const char* _filePath);

		/*bool writeConfigFile(const char* _fileName);*/

		bool hasSetting(std::string _settingName);

		std::string getString(std::string _key);
		int getInt(std::string _key);
		float getFloat(std::string _key);
		double getDouble(std::string _key);
		bool getBool(std::string _key);
		int* getIntArray(std::string _key);
		std::string* getStringArray(std::string _key);
	private:
		LogManager* logManager;
		//FileIO::FileWriter fileWriter;
		FileIO::FileReader fileReader;
		rapidjson::Document document;

		bool getJSONValue(std::string _key, rapidjson::Value &_val);
	};

}