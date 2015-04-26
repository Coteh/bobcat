#include "Mesh.h"

using namespace bobcat;

Mesh::Mesh(std::vector<GLfloat> _vertices, std::vector<GLuint> _elements, std::string _name, std::vector<int> _indiceCountData) {
	m_name = _name;
	indiceCount = _elements.size();
	vertexCount = _vertices.size() / 11;
	m_vertices = _vertices;
	
	refreshMeshAttribMembers();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GLfloat), &m_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceCount * sizeof(GLuint), &_elements[0], GL_STATIC_DRAW);

	m_elements = _elements;
	indiceCountData = _indiceCountData;
	updateDrawModes();

	//Unbind the vertex array when we're done here
	glBindVertexArray(0);

	boundShaderProgram = 0;
}

/*Tried a copy constructor, but values weren't really 
copying over properly, so I am doing this for now.*/
Mesh* Mesh::CopyMesh(const Mesh& _copyMesh){
	return new Mesh(_copyMesh.m_vertices, _copyMesh.m_elements, _copyMesh.m_name, _copyMesh.indiceCountData);
}

Mesh::~Mesh(){
	
}

void Mesh::refreshMeshAttribMembers() {
	//Resize vectors
	m_positions.resize(vertexCount);
	m_normals.resize(vertexCount);
	m_uv.resize(vertexCount);
	m_color.resize(vertexCount);

	//Set the values of each attrib accordingly to each respective value
	//in the vertices vector
	for (size_t i = 0; i < vertexCount; i++) {
		m_positions[i].x = m_vertices[(i * 11) + 0];
		m_positions[i].y = m_vertices[(i * 11) + 1];
		m_positions[i].z = m_vertices[(i * 11) + 2];
		m_normals[i].x = m_vertices[(i * 11) + 3];
		m_normals[i].y = m_vertices[(i * 11) + 4];
		m_normals[i].z = m_vertices[(i * 11) + 5];
		m_uv[i].x = m_vertices[(i * 11) + 6];
		m_uv[i].y = m_vertices[(i * 11) + 7];
		m_color[i].x = m_vertices[(i * 11) + 8];
		m_color[i].y = m_vertices[(i * 11) + 9];
		m_color[i].z = m_vertices[(i * 11) + 10];
	}
}

void Mesh::updateMeshBufferData(std::vector<GLfloat> _vertices) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, _vertices.size() * sizeof(GLfloat), &_vertices[0]);
	m_vertices = _vertices;
}

void Mesh::clearBuffers() {
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glBindVertexArray(0);
}

std::vector<int> Mesh::getIndiceCountData() {
	return indiceCountData;
}

std::vector<GLenum> Mesh::getDrawModes() {
	return drawModeVec;
}

std::string Mesh::getName() {
	return m_name;
}

std::vector<glm::vec3> Mesh::getPositions() {
	return m_positions;
}

std::vector<glm::vec3> Mesh::getNormals() {
	return m_normals;
}

std::vector<glm::vec2> Mesh::getUVs() {
	return m_uv;
}

std::vector<glm::vec3> Mesh::getColor() {
	return m_color;
}

GLuint Mesh::getVAO() {
	return vao;
}

GLuint Mesh::getVBO() {
	return vbo;
}

GLuint Mesh::getEBO() {
	return ebo;
}

int Mesh::getVertexCount() {
	return vertexCount;
}

int Mesh::getIndiceCount() {
	return indiceCount;
}

GLuint Mesh::getBoundShaderProgram() {
	return boundShaderProgram;
}

void Mesh::setName(std::string _name) {
	m_name = _name;
}

void Mesh::setPositions(std::vector<glm::vec3> _pos) {
	m_positions = _pos;
	
	//Hard coded locations in vertice array for now
	std::vector<GLfloat> verties = m_vertices;
	for (size_t i = 0; i < vertexCount; i++) {
		verties[(i * 11) + 0] = m_positions[i].x;
		verties[(i * 11) + 1] = m_positions[i].y;
		verties[(i * 11) + 2] = m_positions[i].z;
	}
	updateMeshBufferData(verties);
}

void Mesh::setNormals(std::vector<glm::vec3> _normals) {
	m_normals = _normals;

	//Hard coded locations in vertice array for now
	std::vector<GLfloat> verties = m_vertices;
	for (size_t i = 0; i < vertexCount; i++) {
		verties[(i * 11) + 3] = m_normals[i].x;
		verties[(i * 11) + 4] = m_normals[i].y;
		verties[(i * 11) + 5] = m_normals[i].z;
	}
	updateMeshBufferData(verties);
}

void Mesh::setUVs(std::vector<glm::vec2> _uvs) {
	m_uv = _uvs;

	//Hard coded locations in vertice array for now
	std::vector<GLfloat> verties = m_vertices;
	for (size_t i = 0; i < vertexCount; i++) {
		verties[(i * 11) + 6] = m_uv[i].x;
		verties[(i * 11) + 7] = m_uv[i].y;
	}
	updateMeshBufferData(verties);
}

void Mesh::setColor(std::vector<glm::vec3> _color) {
	m_color = _color;
	
	//Hard coded locations in vertice array for now
	std::vector<GLfloat> verties = m_vertices;
	for (size_t i = 0; i < vertexCount; i++) {
		verties[(i * 11) + 8] = m_color[i].x;
		verties[(i * 11) + 9] = m_color[i].y;
		verties[(i * 11) + 10] = m_color[i].z;
	}
	updateMeshBufferData(verties);
}

void Mesh::setBoundShaderProgram(GLuint _shaderProgram){
	boundShaderProgram = _shaderProgram;
}

void Mesh::updateDrawModes(){
	drawModeVec = std::vector<GLenum>(0);
	for (size_t i = 0; i < indiceCountData.size(); i++){
		if (indiceCountData[i] > 3){
			drawModeVec.push_back(GL_TRIANGLE_FAN);
		} else if (indiceCountData[i] == 3){
			drawModeVec.push_back(GL_TRIANGLES);
		} else if (indiceCountData[i] == 2){
			drawModeVec.push_back(GL_LINES);
		} else {
			drawModeVec.push_back(GL_POINTS);
		}
	}
}

void Mesh::updateDrawModes(int _glDrawMode){
	drawModeVec = std::vector<GLenum>(0);
	for (size_t i = 0; i < indiceCountData.size(); i++){
		drawModeVec.push_back(_glDrawMode);
	}
}

void Mesh::updateDrawModes(std::vector<GLenum> _drawModesVec){
	drawModeVec = _drawModesVec;
}