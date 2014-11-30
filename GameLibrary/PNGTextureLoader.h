#pragma once
#include "TextureLoader.h"
#include "Texture.h"
#include <SOIL.h>

class PNGTextureLoader : public TextureLoader {
public:
	PNGTextureLoader();
	virtual ~PNGTextureLoader();
	virtual void LoadTextureImage(Texture* _texture, char* _fileName);
};