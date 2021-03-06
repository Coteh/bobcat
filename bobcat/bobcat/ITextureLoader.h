#pragma once
#include "Texture.h"

namespace bobcat {

	/**
	* Abstract class that all texture loaders must derive from and use.
	* Texture loaders can load texture images and store the image data into
	* Texture structures for easy integration into the ResourceManager as well as into Material instances.
	*/
	class ITextureLoader {
	public:
		/**
		* Load a texture image from file.
		* @param _texture Reference to the Texture instance that will receive the image data.
		* @param _filePath Path of the image file to be read.
		*/
		virtual void LoadTextureImage(Texture* _texture, char* _filePath) = 0;

		virtual ~ITextureLoader(){};
	};

}