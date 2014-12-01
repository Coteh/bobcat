#include "TextureManager.h"
#include "PNGTextureLoader.h"
#include "TGATextureLoader.h"
#include <algorithm>
#include <iostream>
#include <sstream>

TextureManager* TextureManager::instance;

TextureManager::TextureManager() {
}

TextureManager* TextureManager::getInstance(){
	if (instance == nullptr){
		instance = new TextureManager();
	}
	return instance;
}

TextureManager::~TextureManager() {
	//Wipes out texture map entirely from memory
	texMap.clear();
	TextureMap clearMap;
	clearMap.swap(texMap);
}

ITextureLoader* TextureManager::determineTextureLoader(std::string _fileName){
	std::istringstream iss(_fileName);
	std::vector<std::string> linesSplit;
	std::string line;
	while (std::getline(iss, line, '.')){
		linesSplit.push_back(line);
	}
	if (linesSplit.size() <= 1){ //no file extension provided. Return a nullptr.
		return nullptr;
	}
	std::string fileExtension = linesSplit[linesSplit.size() - 1];
	std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower);

	if (fileExtension == "png") {
		return new PNGTextureLoader();
	}else if (fileExtension == "tga"){
		return new TGATextureLoader();
	}else{ //format not supported at this time.
		return nullptr;
	}
}

void TextureManager::loadTexture(std::string _fileName, std::string _texName){
	//Provide the file name string to the TextureLoader
	//then load the texture to the brand new texture
	Texture* brandNewTexture = new Texture();
	//Convert string to char array
	char* fileNameChars = new char[_fileName.length() + 1];
	errno_t errCode;
	errCode = strcpy_s(fileNameChars, _fileName.length() + 1, _fileName.c_str());
	//Determine TextureLoader to use
	textureLoader = determineTextureLoader(_fileName);
	if (textureLoader == nullptr) return; //do not load texture if the texture loader is null
	GLuint texID;
	glGenTextures(1, &texID);
	brandNewTexture->texID = texID;
	textureLoader->LoadTextureImage(brandNewTexture, fileNameChars);
	//TextureLoader::LoadTGA(brandNewTexture, fileNameChars);
	//Add brand new texture to the texture map
	texMap[_texName] = brandNewTexture;
}

GLuint TextureManager::getTextureID(std::string _name){
	if (texMap.count(_name)){ //if texture exists...
		return texMap[_name]->texID; //return its ID
	}
	return -1; //otherwise, just return -1
}

Texture* TextureManager::getTexture(std::string _name){
	if (texMap.count(_name)){ //if texture exists...
		return texMap[_name]; //return the texture
	}
	return nullptr; //otherwise, just return a null pointer
}