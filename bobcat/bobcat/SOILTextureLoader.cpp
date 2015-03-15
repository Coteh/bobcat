#include "SOILTextureLoader.h"
#include <SOIL.h>

using namespace bobcat;

SOILTextureLoader::SOILTextureLoader(){

}

SOILTextureLoader::~SOILTextureLoader(){

}

void SOILTextureLoader::LoadTextureImage(Texture* _texture, char* _filePath){
	int width, height;
	unsigned char* image = SOIL_load_image(_filePath, &width, &height, 0, SOIL_LOAD_RGBA);
	_texture->width = width;
	_texture->height = height;
	_texture->type = GL_RGBA;
	_texture->imageData = image;
	_texture->bpp = GL_RGBA;
	//SOIL_free_image_data(image); we will move this to the deconstructor area later
}