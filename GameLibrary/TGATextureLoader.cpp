#include "TGATextureLoader.h"

using namespace bobcat;

GLubyte uTGAcompare[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };	// Uncompressed TGA Header
GLubyte cTGAcompare[12] = { 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0 };	// Compressed TGA Header

TGATextureLoader::TGATextureLoader(){
	
}

TGATextureLoader::~TGATextureLoader(){

}

void TGATextureLoader::LoadTextureImage(Texture* _texture, char* _filePath){
	FILE * fTGA;												// File pointer to texture file
	errno_t errCode;
	errCode = fopen_s(&fTGA, _filePath, "rb");
	//fTGA = fopen(filename, "rb");								// Open file for reading
	//fTGA = fopen("textura_perete.tga","rb");

	if (fTGA == NULL){											// If it didn't open....
		// Display an error message
		logManager->writeLog(LogLevel::LOG_ERROR, "Could not open texture file " + std::string(_filePath));
		logManager->printLastError();
		return;														// Exit function
	}

	if (fread(&tgaHeader, sizeof(TGAHeader), 1, fTGA) == 0)	{				// Attempt to read 12 byte header from file
		// If it fails, display an error message 
		logManager->writeLog(LogLevel::LOG_ERROR, "Could not read file header for texture file " + std::string(_filePath));
		logManager->printLastError();
		if (fTGA != NULL)													// Check to seeiffile is still open
		{
			fclose(fTGA);													// If it is, close it
		}
		return;														// Exit function
	}

	if (memcmp(uTGAcompare, &tgaHeader, sizeof(tgaHeader)) == 0)				// See if header matches the predefined header of 
	{																		// an Uncompressed TGA image
		LoadUncompressedTGA(_texture, _filePath, fTGA);						// If so, jump to Uncompressed TGA loading code
	} else if (memcmp(cTGAcompare, &tgaHeader, sizeof(tgaHeader)) == 0)		// See if header matches the predefined header of
	{																		// an RLE compressed TGA image
		LoadCompressedTGA(_texture, _filePath, fTGA);							// If so, jump to Compressed TGA loading code
	} else	{																// If header matches neither type
		// Display an error
		logManager->writeLog(LogLevel::LOG_ERROR, "TGA file be type 2 or type 10 for texture image " + std::string(_filePath));
		logManager->printLastError();
		fclose(fTGA);
		return;																// Exit function
	}
}

bool TGATextureLoader::LoadCompressedTGA(Texture *_texture, char *_filePath, FILE *_fTGA){
	if (fread(tga.header, sizeof(tga.header), 1, _fTGA) == 0){					// Read TGA header
		// Display error
		logManager->writeLog(LogLevel::LOG_ERROR, "Could not read info header for texture image " + std::string(_filePath));
		logManager->printLastError();
		if (_fTGA != NULL)													// if file is still open
		{
			fclose(_fTGA);													// Close it
		}
		return false;														// Return failular
	}

	_texture->width = tga.header[1] * 256 + tga.header[0];					// Determine The TGA Width	(highbyte*256+lowbyte)
	_texture->height = tga.header[3] * 256 + tga.header[2];					// Determine The TGA Height	(highbyte*256+lowbyte)
	_texture->bpp = tga.header[4];										// Determine the bits per pixel
	tga.Width = _texture->width;										// Copy width into local structure						
	tga.Height = _texture->height;										// Copy height into local structure
	tga.Bpp = _texture->bpp;											// Copy BPP into local structure

	if ((_texture->width <= 0) || (_texture->height <= 0) || ((_texture->bpp != 24) && (_texture->bpp != 32)))	// Make sure all information is valid
	{
		// Display Error
		logManager->writeLog(LogLevel::LOG_ERROR, "Invalid texture information for texture image " + std::string(_filePath));
		logManager->printLastError();
		if (_fTGA != NULL)													// Check if file is still open
		{
			fclose(_fTGA);													// If so, close it
		}
		return false;														// Return failed
	}

	if (_texture->bpp == 24)													// If the BPP of the image is 24...
		_texture->type = GL_RGB;											// Set Image type to GL_RGB
	else																	// Else if its 32 BPP
		_texture->type = GL_RGBA;											// Set image type to GL_RGBA

	tga.bytesPerPixel = (tga.Bpp / 8);									// Compute the number of BYTES per pixel
	tga.imageSize = (tga.bytesPerPixel * tga.Width * tga.Height);		// Compute the total amout ofmemory needed to store data
	_texture->imageData = (GLubyte *)malloc(tga.imageSize);					// Allocate that much memory

	if (_texture->imageData == NULL){											// If no space was allocated
		// Display Error
		logManager->writeLog(LogLevel::LOG_ERROR, "Could not allocate memory for texture image " + std::string(_filePath));
		logManager->printLastError();
		fclose(_fTGA);														// Close the file
		return false;														// Return failed
	}

	if (fread(_texture->imageData, 1, tga.imageSize, _fTGA) != tga.imageSize)	// Attempt to read image data
	{
		// Display Error
		logManager->writeLog(LogLevel::LOG_ERROR, "Could not read image data for texture image " + std::string(_filePath));
		logManager->printLastError();
		if (_texture->imageData != NULL)										// If imagedata has data in it
		{
			free(_texture->imageData);										// Delete data from memory
		}
		fclose(_fTGA);														// Close file
		return false;														// Return failed
	}

	// Byte Swapping Optimized By Steve Thomas
	for (GLuint cswap = 0; cswap < (int)tga.imageSize; cswap += tga.bytesPerPixel)
	{
		_texture->imageData[cswap] ^= _texture->imageData[cswap + 2] ^=
			_texture->imageData[cswap] ^= _texture->imageData[cswap + 2];
	}

	fclose(_fTGA);															// Close file
	return true;
}

bool TGATextureLoader::LoadUncompressedTGA(Texture *_texture, char *_filePath, FILE *_fTGA){
	if (fread(tga.header, sizeof(tga.header), 1, _fTGA) == 0)					// Attempt to read header
	{
		//MessageBox(NULL, "Could not read info header", "ERROR", MB_OK);		// Display Error
		if (_fTGA != NULL)													// If file is open
		{
			fclose(_fTGA);													// Close it
		}
		return false;														// Return failed
	}

	_texture->width = tga.header[1] * 256 + tga.header[0];					// Determine The TGA Width	(highbyte*256+lowbyte)
	_texture->height = tga.header[3] * 256 + tga.header[2];					// Determine The TGA Height	(highbyte*256+lowbyte)
	_texture->bpp = tga.header[4];										// Determine Bits Per Pixel
	tga.Width = _texture->width;										// Copy width to local structure
	tga.Height = _texture->height;										// Copy width to local structure
	tga.Bpp = _texture->bpp;											// Copy width to local structure

	if ((_texture->width <= 0) || (_texture->height <= 0) || ((_texture->bpp != 24) && (_texture->bpp != 32)))	//Make sure all texture info is ok
	{
		//MessageBox(NULL, "Invalid texture information", "ERROR", MB_OK);	// If it isnt...Display error
		if (_fTGA != NULL)													// Check if file is open
		{
			fclose(_fTGA);													// Ifit is, close it
		}
		return false;														// Return failed
	}

	if (_texture->bpp == 24)													// If the BPP of the image is 24...
		_texture->type = GL_RGB;											// Set Image type to GL_RGB
	else																	// Else if its 32 BPP
		_texture->type = GL_RGBA;											// Set image type to GL_RGBA

	tga.bytesPerPixel = (tga.Bpp / 8);									// Compute BYTES per pixel
	tga.imageSize = (tga.bytesPerPixel * tga.Width * tga.Height);		// Compute amout of memory needed to store image
	_texture->imageData = (GLubyte *)malloc(tga.imageSize);					// Allocate that much memory

	if (_texture->imageData == NULL)											// If it wasnt allocated correctly..
	{
		// Display Error
		logManager->writeLog(LogLevel::LOG_ERROR, "Could not allocate memory for texture image " + std::string(_filePath));
		logManager->printLastError();
		fclose(_fTGA);														// Close file
		return false;														// Return failed
	}

	GLuint pixelcount = tga.Height * tga.Width;							// Nuber of pixels in the image
	GLuint currentpixel = 0;												// Current pixel being read
	GLuint currentbyte = 0;												// Current byte 
	GLubyte * colorbuffer = (GLubyte *)malloc(tga.bytesPerPixel);			// Storage for 1 pixel

	do
	{
		GLubyte chunkheader = 0;											// Storage for "chunk" header

		if (fread(&chunkheader, sizeof(GLubyte), 1, _fTGA) == 0)				// Read in the 1 byte header
		{
			// Display Error
			logManager->writeLog(LogLevel::LOG_ERROR, "Could not read RLE header for texture image " + std::string(_filePath));
			logManager->printLastError();
			if (_fTGA != NULL)												// If file is open
			{
				fclose(_fTGA);												// Close file
			}
			if (_texture->imageData != NULL)									// If there is stored image data
			{
				free(_texture->imageData);									// Delete image data
			}
			return false;													// Return failed
		}

		if (chunkheader < 128)												// If the ehader is < 128, it means the that is the number of RAW color packets minus 1
		{																	// that follow the header
			chunkheader++;													// add 1 to get number of following color values
			for (short counter = 0; counter < chunkheader; counter++)		// Read RAW color values
			{
				if (fread(colorbuffer, 1, tga.bytesPerPixel, _fTGA) != tga.bytesPerPixel) // Try to read 1 pixel
				{
					// IF we cant, display an error
					logManager->writeLog(LogLevel::LOG_ERROR, "Could not read image data for texture image " + std::string(_filePath));
					logManager->printLastError();

					if (_fTGA != NULL)													// See if file is open
					{
						fclose(_fTGA);													// If so, close file
					}

					if (colorbuffer != NULL)												// See if colorbuffer has data in it
					{
						free(colorbuffer);												// If so, delete it
					}

					if (_texture->imageData != NULL)										// See if there is stored Image data
					{
						free(_texture->imageData);										// If so, delete it too
					}

					return false;														// Return failed
				}
				// write to memory
				_texture->imageData[currentbyte] = colorbuffer[2];				    // Flip R and B vcolor values around in the process 
				_texture->imageData[currentbyte + 1] = colorbuffer[1];
				_texture->imageData[currentbyte + 2] = colorbuffer[0];

				if (tga.bytesPerPixel == 4)												// if its a 32 bpp image
				{
					_texture->imageData[currentbyte + 3] = colorbuffer[3];				// copy the 4th byte
				}

				currentbyte += tga.bytesPerPixel;										// Increase thecurrent byte by the number of bytes per pixel
				currentpixel++;															// Increase current pixel by 1

				if (currentpixel > pixelcount)											// Make sure we havent read too many pixels
				{
					// if there is too many... Display an error!
					logManager->writeLog(LogLevel::LOG_ERROR, "Too many pixels read for texture image " + std::string(_filePath));
					logManager->printLastError();

					if (_fTGA != NULL)													// If there is a file open
					{
						fclose(_fTGA);													// Close file
					}

					if (colorbuffer != NULL)												// If there is data in colorbuffer
					{
						free(colorbuffer);												// Delete it
					}

					if (_texture->imageData != NULL)										// If there is Image data
					{
						free(_texture->imageData);										// delete it
					}

					return false;														// Return failed
				}
			}
		} else																			// chunkheader > 128 RLE data, next color reapeated chunkheader - 127 times
		{
			chunkheader -= 127;															// Subteact 127 to get rid of the ID bit
			if (fread(colorbuffer, 1, tga.bytesPerPixel, _fTGA) != tga.bytesPerPixel)		// Attempt to read following color values
			{
				// If attempt fails.. Display error (again)
				logManager->writeLog(LogLevel::LOG_ERROR, "Could not read from file for texture image " + std::string(_filePath));
				logManager->printLastError();

				if (_fTGA != NULL)														// If thereis a file open
				{
					fclose(_fTGA);														// Close it
				}

				if (colorbuffer != NULL)													// If there is data in the colorbuffer
				{
					free(colorbuffer);													// delete it
				}

				if (_texture->imageData != NULL)											// If thereis image data
				{
					free(_texture->imageData);											// delete it
				}

				return false;															// return failed
			}

			for (short counter = 0; counter < chunkheader; counter++)					// copy the color into the image data as many times as dictated 
			{																			// by the header
				_texture->imageData[currentbyte] = colorbuffer[2];					// switch R and B bytes areound while copying
				_texture->imageData[currentbyte + 1] = colorbuffer[1];
				_texture->imageData[currentbyte + 2] = colorbuffer[0];

				if (tga.bytesPerPixel == 4)												// If TGA images is 32 bpp
				{
					_texture->imageData[currentbyte + 3] = colorbuffer[3];				// Copy 4th byte
				}

				currentbyte += tga.bytesPerPixel;										// Increase current byte by the number of bytes per pixel
				currentpixel++;															// Increase pixel count by 1

				if (currentpixel > pixelcount)											// Make sure we havent written too many pixels
				{
					// if there is too many... Display an error!
					logManager->writeLog(LogLevel::LOG_ERROR, "Too many pixels read for texture image " + std::string(_filePath));
					logManager->printLastError();

					if (_fTGA != NULL)													// If there is a file open
					{
						fclose(_fTGA);													// Close file
					}

					if (colorbuffer != NULL)												// If there is data in colorbuffer
					{
						free(colorbuffer);												// Delete it
					}

					if (_texture->imageData != NULL)										// If there is Image data
					{
						free(_texture->imageData);										// delete it
					}

					return false;														// Return failed
				}
			}
		}
	}

	while (currentpixel < pixelcount);													// Loop while there are still pixels left
	fclose(_fTGA);																		// Close the file
	return true;
}