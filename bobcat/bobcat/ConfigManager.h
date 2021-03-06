#pragma once
#include "LogManager.h"
#include "FileReader.h"
#include "AbstractWindower.h"
#include <rapidjson\document.h>

#define CFG_KEY_WINDOW "window"
#define CFG_KEY_ASSETPATHS "content-paths"
#define CFG_KEY_LOGSETTINGS "log-settings"

namespace bobcat {

	struct AssetPaths {
		std::string modelPath;
		std::string texPath;
		std::string shadersPath;
	};

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
		* @param _filePath File path of the configuration file to read.
		*/
		void readConfigFile(const char* _filePath);

		/*bool writeConfigFile(const char* _fileName);*/

		/**
		* Get window settings from the configuration file.
		* @param &_name Reference to name variable to overwrite.
		* @param &_width Reference to width variable to overwrite.
		* @param &_height Reference to height variable to overwrite.
		*/
		bool getWindowSettings(WindowSettings* _windowSettings);

		bool getAssetLoadPaths(AssetPaths* _assetPaths);

		bool getLogSettings(LogSettings* _logSettings);
	};

}