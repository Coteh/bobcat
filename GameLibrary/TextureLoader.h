#pragma once
#include "vgl.h"
#include "Texture.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

