#include "GameObject.h"


GameObject::GameObject(){
	angle = 0;
	position = glm::vec3(0.0f, 0.0f, 0.0f);
}

GameObject::~GameObject() {
	
}

std::string GameObject::getName(){
	return name;
}

void GameObject::setName(std::string _name){
	name = _name;
}

void GameObject::setMesh(Mesh* _mesh) {
	mesh = _mesh;
}

void GameObject::setDrawMode(GLenum _drawMode){
	drawMode = _drawMode;
}

void GameObject::setPosition(float _x, float _y, float _z){
	position.x = _x;
	position.y = _y;
	position.z = _z;
}

void GameObject::Update(float _gameTime){
	angle += 1 * _gameTime;
	if (angle >= 360.0f){
		angle = 0.0f;
	}
	ModelMat = glm::translate(position) * glm::rotate(angle, glm::vec3(0.0f, 1.0f, 1.0f));
}

void GameObject::Draw(GLuint _modelLoc){
	glUniformMatrix4fv(_modelLoc, 1, GL_FALSE, glm::value_ptr(ModelMat));
	glBindVertexArray(mesh->getVAO());
	glDrawElements(drawMode, mesh->getCount(), GL_UNSIGNED_INT, (void*)0);
}
