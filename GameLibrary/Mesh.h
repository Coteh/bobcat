#pragma once

#include <vector>
#include <string>
#include "vgl.h"
#include "Shader.h"

class Mesh{
private:
	GLuint vbo, ebo, vao;
	std::vector<int> indiceCountData;
	int count;
	std::string name;
	Shader* shader;
public:
	Mesh(){}
	Mesh(std::vector<GLfloat> _vertices, std::vector<GLuint> _elements, std::string _name, std::vector<int> _indiceCountData, Shader* _shader);
	~Mesh();
	GLuint getVAO();
	GLuint getEBO();
	Shader* getShader();
	int getCount();
	std::vector<int> getIndiceCountData();
	std::string getName();
	void setShader(Shader* _shader);
};