#pragma once
#include "vgl.h"

namespace bobcat {

	class Texture {
	public:
		GLubyte	* imageData;									// Image Data (Up To 32 Bits)
		GLuint	bpp;											// Image Color Depth In Bits Per Pixel
		GLuint	width;											// Image Width
		GLuint	height;											// Image Height
		GLuint  depth;											// Image Depth
		GLuint	texID;											// Texture ID Used To Select A Texture
		GLuint	type;											// Image Type (GL_RGB, GL_RGBA)

		GLenum textureType;										// Texture Type (GL_TEXTURE_2D, GL_TEXTURE_3D)

		Texture();
		~Texture();
		void Bind(int _mode, GLuint _samplerLoc);
		void Bind(GLuint _samplerLoc);
		void Unbind();
	};

}