#include "GameObject.h"


GameObject::GameObject(){
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	setFriction(1.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

GameObject::~GameObject() {
	
}

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

Collider* GameObject::getCollider(){
	return collider;
}

Mesh* GameObject::getMesh(){
	return mesh;
}

Shader* GameObject::getShader(){
	return shader;
}

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

void GameObject::setFriction(float _fric){
	friction = _fric;
}

void GameObject::setRotationEuler(float _x, float _y, float _z){
	rotation.x = _x;
	rotation.y = _y;
	rotation.z = _z;
}

void GameObject::setScale(float _x, float _y, float _z){
	scale = glm::vec3(_x, _y, _z);
}

void GameObject::setShader(Shader* _shader) {
	shader = _shader;
}

void GameObject::setTexture(Texture* _tex){
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

void GameObject::attachGameObject(GameObject* _gameObject){
	children.push_back(_gameObject);
	_gameObject->parent = this;
}

void GameObject::Update(float _gameTime){
	velocity *= friction;
	for (int i = 0; i < children.size(); i++){
		children[i]->Update(_gameTime);
	}
}

void GameObject::Draw(){
	/*glBindBuffer(GL_ARRAY_BUFFER, tex->texID);
	glDrawElements(GL_TEXTURE_2D, uvCords.size(), GL_UNSIGNED_INT, (void*)0);*/
	if (mesh == nullptr)return; //Don't do any drawing if there's no mesh attached to the object
	glBindVertexArray(mesh->getVAO());
	if (isWireFrameOn){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	int indicesSoFar = 0;
	for (int i = 0; i < drawModeVec.size(); i++){
		glDrawElements(drawModeVec[i], indiceCountData[i], GL_UNSIGNED_INT, (void*)(indicesSoFar * sizeof(GLuint)));
		indicesSoFar += indiceCountData[i];
	}
	if (isWireFrameOn){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glBindVertexArray(0);
}