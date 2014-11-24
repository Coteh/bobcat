#include "Mesh.h"

Mesh::Mesh(std::vector<GLfloat> _vertices, std::vector<GLuint> _elements, std::string _name, std::vector<int> _indiceCountData){
	name = _name;
	count = _elements.size();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(GLfloat), &_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), &_elements[0], GL_STATIC_DRAW);

	indiceCountData = _indiceCountData;

	//Unbind the vertex array when we're done here
	glBindVertexArray(0);
}

Mesh::~Mesh(){
	
}

void Mesh::clearBuffers(){
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glBindVertexArray(0);
}

std::vector<int> Mesh::getIndiceCountData(){
	return indiceCountData;
}

std::string Mesh::getName(){
	return name;
}

GLuint Mesh::getVAO(){
	return vao;
}

GLuint Mesh::getVBO(){
	return vbo;
}

GLuint Mesh::getEBO(){
	return ebo;
}

int Mesh::getCount(){
	return count;
}