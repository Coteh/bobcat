#include "Mesh.h"

Mesh::Mesh(std::vector<GLfloat> _vertices, std::vector<GLuint> _elements, std::string _name, std::vector<int> _indiceCountData, Shader* _shader){
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

	setShader(_shader);
}

Mesh::~Mesh(){
	glBindVertexArray(0);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
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

GLuint Mesh::getEBO(){
	return ebo;
}

Shader* Mesh::getShader(){
	return shader;
}

int Mesh::getCount(){
	return count;
}

void Mesh::setShader(Shader* _shader){
	shader = _shader;

	glBindVertexArray(vao);

	/*Specify that our coordinate data is going into attribute index 0 (vPosition), and contains
	three floats per vertex*/
	glVertexAttribPointer(shader->posAttrib, 3, GL_FLOAT,
		GL_FALSE, 11 * sizeof(GLfloat), 0);
	/*Specify that our normal data is going into attribute index 1 (vNormals), and contains
	three floats per vertex*/
	glVertexAttribPointer(shader->normAttrib, 3, GL_FLOAT,
		GL_FALSE, 11 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	/*Specify that our uv data is going into attribute index 2 (vTexture), and contains
	two floats per vertex*/
	glVertexAttribPointer(shader->texAttrib, 2, GL_FLOAT,
		GL_FALSE, 11 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	/*Specify that our color data is going into attribute index 3 (vColor), and contains
	three ints per vertex*/
	glVertexAttribPointer(shader->colAttrib, 3, GL_FLOAT,
		GL_FALSE, 11 * sizeof(GLfloat), (void*)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(shader->posAttrib);
	glEnableVertexAttribArray(shader->normAttrib);
	glEnableVertexAttribArray(shader->texAttrib);
	glEnableVertexAttribArray(shader->colAttrib);

	//Unbind the vertex array when we're done here
	glBindVertexArray(0);
}