#include "Texture.h"

using namespace bobcat;

Texture::Texture(){
	textureType = GL_TEXTURE_2D; //default texture type is 2D
}

Texture::~Texture(){

}

void Texture::Bind(int _mode, GLuint _samplerLoc) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(_mode, texID);
	glUniform1i(_samplerLoc, 0);
}

void Texture::Bind(GLuint _samplerLoc){
	Bind(textureType, _samplerLoc);
}

void Texture::Unbind(){
	glBindTexture(textureType, 0);
}