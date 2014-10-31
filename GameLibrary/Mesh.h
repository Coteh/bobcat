#pragma once

#include <vector>
#include <string>
#include "vgl.h"

class Mesh{
private:
	GLuint vbo, ebo, vao;
	int count;
	std::string name;
public:
	Mesh(){}
	Mesh(std::vector<GLfloat> _vertices, std::vector<GLuint> _elements, std::string _name);
	~Mesh();
	GLuint getVAO();
	int getCount();
	std::string getName();
};