#pragma once
#include "vgl.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct Texture {
	GLubyte	* imageData;									// Image Data (Up To 32 Bits)
	GLuint	bpp;											// Image Color Depth In Bits Per Pixel
	GLuint	width;											// Image Width
	GLuint	height;											// Image Height
	GLuint	texID;											// Texture ID Used To Select A Texture
	GLuint	type;											// Image Type (GL_RGB, GL_RGBA)
};

struct TGAHeader {
	GLubyte Header[12];									// TGA File Header
};

struct TGA {
	GLubyte		header[6];								// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;							// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;								// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;									// Temporary Variable
	GLuint		type;
	GLuint		Height;									//Height of Image
	GLuint		Width;									//Width ofImage
	GLuint		Bpp;									// Bits Per Pixel
};

class TextureLoader {
public:
	static bool LoadTGA(Texture * texture, char * filename);
	static bool LoadCompressedTGA(Texture * texture, char * filename, FILE * fTGA);
	static bool LoadUncompressedTGA(Texture * texture, char * filename, FILE * fTGA);
};

