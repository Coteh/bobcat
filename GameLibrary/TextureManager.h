#pragma once
#include "vgl.h"
#include "TextureLoader.h"
#include <map>
class TextureManager {
private:
	static TextureManager* instance;
	typedef std::map<const std::string, Texture> TextureMap;
	TextureMap texMap;
	TextureManager();
public:
	static TextureManager* getInstance();
	void loadTexture(std::string _fileName, std::string _texName);
	GLuint getTextureID(std::string _name);
	Texture getTexture(std::string _name);
	~TextureManager();
};

