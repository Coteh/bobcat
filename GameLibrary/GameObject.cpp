#include "GameObject.h"
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

GameObject::GameObject(){
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	setFriction(1.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

GameObject::~GameObject() {
	
}

/**
* GET METHODS
*/

std::vector<GameObject*> GameObject::getChildren(){
	return children;
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

glm::vec3 GameObject::getVelocity(){
	return velocity;
}

glm::vec3 GameObject::getRotation(){
	return rotation;
}

glm::vec3 GameObject::getRotationalVel(){
	return rotationalVel;
}

Collider* GameObject::getCollider(){
	return collider;
}

Mesh* GameObject::getMesh(){
	return mesh;
}

Shader* GameObject::getShader(){
	return shader;
}

/**
* SET METHODS
*/

void GameObject::setName(std::string _name){
	name = _name;
}

void GameObject::setMesh(Mesh* _mesh) {
	mesh = _mesh;
	indiceCountData = mesh->getIndiceCountData();
	drawModeVec = mesh->getDrawModes();
}

void GameObject::setCollider(Collider* _collider){
	collider = _collider;
	collider->setPosition(position);
}

void GameObject::setPosition(float _x, float _y, float _z){
	setPosition(glm::vec3(_x, _y, _z));
}

void GameObject::setPosition(glm::vec3 _pos){
	position = _pos;
	if (collider != nullptr) collider->setPosition(_pos);
}

void GameObject::setVelocity(float _x, float _y, float _z){
	setVelocity(glm::vec3(_x, _y, _z));
}

void GameObject::setVelocity(glm::vec3 _vel){
	velocity = _vel;
}

void GameObject::setFriction(float _fric){
	friction = _fric;
}

void GameObject::setRotationEuler(float _x, float _y, float _z){
	setRotationEuler(glm::vec3(_x, _y, _z));
}

void GameObject::setRotationEuler(glm::vec3 _rotEuler){
	rotation = _rotEuler;
}

void GameObject::setRotationalVel(float _x, float _y, float _z){
	setRotationalVel(glm::vec3(_x, _y, _z));
}

void GameObject::setRotationalVel(glm::vec3 _rotVel){
	rotationalVel = _rotVel;
}

void GameObject::setScale(float _x, float _y, float _z){
	scale = glm::vec3(_x, _y, _z);
}

void GameObject::setShader(Shader* _shader) {
	shader = _shader;
}

void GameObject::setTexture(Texture* _tex){
	if (_tex == nullptr) return; //can't set a null texture!
	tex = _tex;
	glBindTexture(GL_TEXTURE_3D, _tex->texID);

	glTexImage2D(GL_TEXTURE_2D, 0, _tex->bpp, _tex->width, _tex->height, 0, _tex->type, GL_UNSIGNED_BYTE, _tex->imageData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_3D, 0);
}

/**
* OTHER METHODS
*/

void GameObject::attachGameObject(GameObject* _gameObject){
	children.push_back(_gameObject);
	_gameObject->parent = this;
}

void GameObject::Update(float _deltaTime){
	velocity *= friction;
	rotation += rotationalVel * _deltaTime;
	for (size_t i = 0; i < children.size(); i++){
		children[i]->Update(_deltaTime);
	}
}

void GameObject::Draw(){
	if (mesh == nullptr)return; //Don't do any drawing if there's no mesh attached to the object
	glBindVertexArray(mesh->getVAO());
	if (isWireFrameOn){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	int indicesSoFar = 0;
	for (size_t i = 0; i < drawModeVec.size(); i++){
		glDrawElements(drawModeVec[i], indiceCountData[i], GL_UNSIGNED_INT, (void*)(indicesSoFar * sizeof(GLuint)));
		indicesSoFar += indiceCountData[i];
	}
	if (isWireFrameOn){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glBindVertexArray(0);
}