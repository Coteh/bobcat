#pragma once
#include <GL\glew.h>
#include "IModelReader.h"
#include "FileReader.h"

#define PLY_MAGIC_NUMBER "ply"
#define PLY_FORMAT_STRING "format"
#define PLY_COMMENT_STRING "comment"
#define PLY_ELEMENT_STRING "element"
#define PLY_PROPERTY_STRING "property"
#define PLY_END_HEADER_STRING "end_header"

class PLYModelReader : public IModelReader, public FileReader {
private:
	typedef std::vector<std::string> PlyFormatStorage;
	PlyFormatStorage fileContents;
	PlyFormatStorage::iterator fileIterator;
	enum PLY_FILE_FORMAT{
		ASCII_1_0 = 0,
		BINARY_LITTLE_ENDIAN_1_0 = 1,
		BINARY_BIG_ENDIAN_1_0 = 2
	};
	PLY_FILE_FORMAT plyFormat;
	enum PLY_READ_STAGE{
		NONE = 0,
		HEADER = 1,
		VERTICES = 2,
		INDICES = 4
	};
	PLY_READ_STAGE plyReadStage;
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
public:
	PLYModelReader();
	virtual ~PLYModelReader();
	virtual void readModel(std::string _fileName);
	std::pair<std::vector<GLfloat>, std::vector<GLuint>> getModelData();
};

