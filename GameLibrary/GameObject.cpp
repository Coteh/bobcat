#include "GameObject.h"


GameObject::GameObject(){
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_3D, tex);

	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	collisionRect = Rect3D();
}

GameObject::~GameObject() {
	
}

std::string GameObject::getName(){
	return name;
}

glm::mat4 GameObject::getModelMat(){
	glm::mat4 model = glm::translate(position);
	model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
	model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
	model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));
	model = glm::scale(model, scale);
	if (parent){
		model = parent->getModelMat() * model;
	}
	return model;
}

glm::vec3 GameObject::getPosition(){
	return position;
}

glm::vec3 GameObject::getRotation(){
	return rotation;
}

Rect3D GameObject::getCollisionRect(){
	return collisionRect;
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

void GameObject::setPosition(glm::vec3 _pos){
	position = _pos;
}

void GameObject::setVelocity(float _x, float _y, float _z){
	velocity.x = _x;
	velocity.y = _y;
	velocity.z = _z;
}

void GameObject::setRotationEuler(float _x, float _y, float _z){
	rotation.x = _x;
	rotation.y = _y;
	rotation.z = _z;
}

void GameObject::setScale(float _x, float _y, float _z){
	scale = glm::vec3(_x, _y, _z);
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
