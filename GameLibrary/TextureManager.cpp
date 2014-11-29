#include "TextureManager.h"

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

void TextureManager::loadTexture(std::string _fileName, std::string _texName){
	//Provide the file name string to the TextureLoader
	//then load the texture to the brand new texture
	Texture* brandNewTexture = new Texture();
	//Convert string to char array
	char* fileNameChars = new char[_fileName.length() + 1];
	errno_t errCode;
	errCode = strcpy_s(fileNameChars, _fileName.length() + 1, _fileName.c_str());
	//Determine TextureLoader to use
	//fuck it, we're doing pngs for now
	textureLoader = new PNGTextureLoader();
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