#pragma once
#include "ITextureLoader.h"
#include "Texture.h"
#include <SOIL.h>

class PNGTextureLoader : public ITextureLoader {
public:
	PNGTextureLoader();
	virtual ~PNGTextureLoader();
	virtual void LoadTextureImage(Texture* _texture, char* _fileName);
};