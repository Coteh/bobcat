#pragma once
#include "TextureLoader.h"
#include "LogManager.h"
#include <stdio.h>

namespace bobcat {

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

	class TGATextureLoader : public TextureLoader {
	private:
		TGAHeader tgaHeader; // TGA Header
		TGA tga;			// TGA image data
	public:
		TGATextureLoader();
		virtual ~TGATextureLoader();
		virtual void LoadTextureImage(Texture* _texture, char* _filePath);
		bool LoadCompressedTGA(Texture *_texture, char *_filePath, FILE *_fTGA);
		bool LoadUncompressedTGA(Texture *_texture, char *_filePath, FILE *_fTGA);
	};

}