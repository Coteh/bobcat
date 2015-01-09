#include "Texture.h"

using namespace bobcat;

Texture::Texture(){

}

Texture::~Texture(){

}

void Texture::Bind(GLuint _samplerLoc){
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);
	glUniform1i(_samplerLoc, 0);
}