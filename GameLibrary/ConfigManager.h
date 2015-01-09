#pragma once
#include "LogManager.h"
#include "FileReader.h"
#include <rapidjson\document.h>

#define CFG_KEY_WINDOW "window"

namespace bobcat {

	/**
	* A singleton class that can open up a JSON configuration file and read properties from it.
	*/
	class ConfigManager {
	private:
		static ConfigManager* instance;
		LogManager* logManager;
		FileIO::FileWriter fileWriter;
		FileIO::FileReader fileReader;
		rapidjson::Document document;
		ConfigManager();
	public:
		/**
		* Get the Singleton instance.
		*/
		static ConfigManager* getInstance();

		~ConfigManager();

		/**
		* Read a configuration file.
		* @param _fileName File name of the configuration file to read.
		*/
		void readConfigFile(const char* _fileName);

		/*bool writeConfigFile(const char* _fileName);*/

		/**
		* Get window settings from the configuration file.
		* @param &_name Reference to name variable to overwrite.
		* @param &_width Reference to width variable to overwrite.
		* @param &_height Reference to height variable to overwrite.
		*/
		void getWindowSettings(const char* &_name, int &_width, int &_height);
	};

}