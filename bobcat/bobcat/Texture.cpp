#include "Texture.h"

using namespace bobcat;

Texture::Texture(){

}

Texture::~Texture(){

}

void Texture::Bind(int _mode, GLuint _samplerLoc) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(_mode, texID);
	glUniform1i(_samplerLoc, 0);
}

void Texture::Bind(GLuint _samplerLoc){
	Bind(GL_TEXTURE_2D, _samplerLoc);
}