#pragma once
#include "Texture.h"

class ITextureLoader {
public:
	virtual ~ITextureLoader(){};
	virtual void LoadTextureImage(Texture* _texture, char* _fileName) = 0;
};