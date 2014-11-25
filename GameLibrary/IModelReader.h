#pragma once
#include <string>
#include <GL\glew.h>
#include <vector>

class IModelReader {
public:
	virtual void readModel(std::string _fileName) = 0;
	virtual ~IModelReader(){};
	virtual std::vector<GLfloat> getAllVertexData() = 0;
	virtual std::vector<GLuint> getIndices() = 0;
	virtual std::vector<int> getIndiceCountData() = 0;
};

