#pragma once
#include "ITextureLoader.h"
#include "LogManager.h"

class TextureLoader : public ITextureLoader {
protected:
	LogManager* logManager;
public:
	TextureLoader(){
		logManager = LogManager::getInstance();
	}
	virtual ~TextureLoader(){};
	virtual void LoadTextureImage(Texture* _texture, char* _fileName){
		logManager->writeLog(LogLevel::LOG_ERROR, "Please specify a format for loading texture image.");
		logManager->printLastError();
	};
};

