#pragma once
#include "vgl.h"

namespace bobcat {

	class Texture {
	public:
		GLubyte	* imageData;									// Image Data (Up To 32 Bits)
		GLuint	bpp;											// Image Color Depth In Bits Per Pixel
		GLuint	width;											// Image Width
		GLuint	height;											// Image Height
		GLuint	texID;											// Texture ID Used To Select A Texture
		GLuint	type;											// Image Type (GL_RGB, GL_RGBA)

		Texture();
		~Texture();
		void Bind(GLuint _samplerLoc);
	};

}