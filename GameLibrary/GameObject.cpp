#include "GameObject.h"
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

GameObject::GameObject(){
	setFriction(1.0f);
	color = glm::vec4(1.0f);
}

GameObject::GameObject(GameObjectConstructionInfo* _constructionInfo) : GameObject(){
	if (_constructionInfo->transform != nullptr) setTransform(_constructionInfo->transform);
	if (_constructionInfo->collider != nullptr) setCollider(_constructionInfo->collider);
	if (_constructionInfo->mesh != nullptr) setMesh(_constructionInfo->mesh);
	if (_constructionInfo->shader != nullptr) setShader(_constructionInfo->shader);
	if (_constructionInfo->texture != nullptr) setTexture(_constructionInfo->texture);
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
	glm::mat4 model = glm::mat4(1.0f);
	if (transform != nullptr){
		model = glm::translate(transform->position);
		glm::vec3 rot = transform->rotation; //to cut down on the amount of times we're getting rotation
		model = glm::rotate(model, rot.x, glm::vec3(1, 0, 0));
		model = glm::rotate(model, rot.y, glm::vec3(0, 1, 0));
		model = glm::rotate(model, rot.z, glm::vec3(0, 0, 1));
		model = glm::scale(model, transform->scale);
	}
	if (parent){
		model = parent->getModelMat() * model;
	}
	return model;
}

glm::vec3 GameObject::getVelocity(){
	return velocity;
}

glm::vec3 GameObject::getRotationalVel(){
	return rotationalVel;
}

glm::vec4 GameObject::getColor(){
	return color;
}

Transform* GameObject::getTransform(){
	return transform;
}

Collider* GameObject::getCollider(){
	return collider;
}

MeshRenderer* GameObject::getMeshRenderer(){
	return meshRenderer;
}

Shader* GameObject::getShader(){
	return shader;
}

Texture* GameObject::getTexture(){
	return tex;
}

/**
* SET METHODS
*/

void GameObject::setName(std::string _name){
	name = _name;
}

/**
* I wanted to get rid of the Mesh from GameObject but looks
* like it's not gone yet! :P
*/
void GameObject::setMesh(Mesh* _mesh) {
	meshRenderer = new MeshRenderer();
	meshRenderer->mesh = _mesh;
	meshRenderer->CalibrateMeshData();
	meshRenderer->isEnabled = true;
}

void GameObject::setTransform(Transform* _transform){
	transform = _transform;
	transform->gameObject = this;
	transform->collider = collider;
	if (collider != nullptr){
		collider->transform = transform;
	}
}

void GameObject::setCollider(Collider* _collider){
	collider = _collider;
	collider->gameObject = this;
	collider->transform = transform;
	if (transform != nullptr){
		transform->collider = collider;
	}
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

void GameObject::setRotationalVel(float _x, float _y, float _z){
	setRotationalVel(glm::vec3(_x, _y, _z));
}

void GameObject::setRotationalVel(glm::vec3 _rotVel){
	rotationalVel = _rotVel;
}

void GameObject::setColor(glm::vec4 _color){
	color = _color;
}

void GameObject::setShader(Shader* _shader) {
	shader = _shader;
}

void GameObject::setTexture(Texture* _tex){
	if (_tex == nullptr) return; //can't set a null texture!
	tex = _tex;
}

/**
* OTHER METHODS
*/

void GameObject::attachGameObject(GameObject* _gameObject){
	children.push_back(_gameObject);
	_gameObject->parent = this;
}

void GameObject::Update(float _deltaTime){
	if (transform != nullptr){
		transform->position += velocity * _deltaTime;
		transform->rotation += rotationalVel * _deltaTime;
	}
	for (size_t i = 0; i < children.size(); i++){
		children[i]->Update(_deltaTime);
	}
	velocity *= friction;
}

void GameObject::Draw(){
	if (meshRenderer->mesh != nullptr){
		meshRenderer->Render();
	}
}