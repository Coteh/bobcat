#include "GameObject.h"


GameObject::GameObject(){
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_3D, tex);

	angle = 0;
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotAxis = glm::vec3(1.0f, 1.0f, 1.0f);
}

GameObject::~GameObject() {
	
}

std::string GameObject::getName(){
	return name;
}

glm::mat4 GameObject::getModelMat(){
	glm::mat4 model = glm::translate(position) * glm::rotate(angle, glm::vec3(rotAxis.x, rotAxis.y, rotAxis.z));
	if (parent){
		model = parent->getModelMat() * model;
	}
	return model;
}

void GameObject::setName(std::string _name){
	name = _name;
}

void GameObject::setMesh(Mesh* _mesh) {
	mesh = _mesh;
	UpdateDrawModes();
}

void GameObject::setCollisionRect(Rect3D _rect){
	collisionRect = _rect;
}

void GameObject::setPosition(float _x, float _y, float _z){
	position.x = _x;
	position.y = _y;
	position.z = _z;
}

void GameObject::setVelocity(float _x, float _y, float _z){
	velocity.x = _x;
	velocity.y = _y;
	velocity.z = _z;
}

void GameObject::setTorque(float _torque){
	torque = _torque;
}

void GameObject::setRotAxis(float _x, float _y, float _z){
	rotAxis.x = _x;
	rotAxis.y = _y;
	rotAxis.z = _z;
}

void GameObject::attachGameObject(GameObject* _gameObject){
	children.push_back(_gameObject);
	_gameObject->parent = this;
}

void GameObject::UpdateDrawModes(){
	indiceCountData = mesh->getIndiceCountData();
	for (int i = 0; i < indiceCountData.size(); i++){
		if (indiceCountData[i] > 3){
			drawModeVec.push_back(GL_TRIANGLE_FAN);
		} else{
			drawModeVec.push_back(GL_TRIANGLES);
		}
	}
}

void GameObject::Update(float _gameTime){
	angle += torque * _gameTime;
	if (angle >= 360.0f){
		angle = 0.0f;
	}
	position += velocity * _gameTime;
	velocity *= 0.97f;
	for (int i = 0; i < children.size(); i++){
		children[i]->Update(_gameTime);
	}
}

void GameObject::Draw(GLuint _modelLoc){
	glUniformMatrix4fv(_modelLoc, 1, GL_FALSE, glm::value_ptr(getModelMat()));
	glBindVertexArray(mesh->getVAO());
	//glDrawElements(drawMode, mesh->getCount(), GL_UNSIGNED_INT, (void*)0);
	int indicesSoFar = 0;
	for (int i = 0; i < drawModeVec.size(); i++){
		glDrawElements(drawModeVec[i], indiceCountData[i], GL_UNSIGNED_INT, (void*)(indicesSoFar * sizeof(GLuint)));
		indicesSoFar += indiceCountData[i];
	}
	for (int i = 0; i < children.size(); i++){
		children[i]->Draw(_modelLoc);
	}
}
