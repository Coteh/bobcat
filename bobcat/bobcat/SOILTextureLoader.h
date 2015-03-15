#pragma once
#include "TextureLoader.h"
#include "Texture.h"

namespace bobcat {

	class SOILTextureLoader : public TextureLoader {
	public:
		SOILTextureLoader();
		virtual ~SOILTextureLoader();
		virtual void LoadTextureImage(Texture* _texture, char* _filePath);
	};

}