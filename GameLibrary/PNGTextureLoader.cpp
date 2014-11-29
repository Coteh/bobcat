#include "PNGTextureLoader.h"

PNGTextureLoader::PNGTextureLoader(){

}

PNGTextureLoader::~PNGTextureLoader(){

}

void PNGTextureLoader::LoadTextureImage(Texture* _texture, char* _fileName){
	int width, height;
	unsigned char* image = SOIL_load_image(_fileName, &width, &height, 0, SOIL_LOAD_RGB);
	/*glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);*/
	_texture->width = width;
	_texture->height = height;
	_texture->type = GL_RGB;
	_texture->imageData = image;
	_texture->bpp = GL_RGB;
	//SOIL_free_image_data(image); we will move this to the deconstructor area later
}