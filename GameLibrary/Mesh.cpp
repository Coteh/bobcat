#include "Mesh.h"

Mesh::Mesh(std::vector<GLfloat> _vertices, std::vector<GLuint> _elements, std::string _name){
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

	/*Specify that our coordinate data is going into attribute index 0 (vPosition), and contains
	three floats per vertex*/
	glVertexAttribPointer(0, 3, GL_FLOAT,
		GL_FALSE, 0, BUFFER_OFFSET(0));
	/*Enable attribute index 0 (vPosition) as being used*/
	glEnableVertexAttribArray(0);
}

Mesh::~Mesh(){
	glBindVertexArray(0);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

std::string Mesh::getName(){
	return name;
}

GLuint Mesh::getVAO(){
	return vao;
}

int Mesh::getCount(){
	return count;
}