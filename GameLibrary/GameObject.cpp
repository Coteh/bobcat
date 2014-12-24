#include "GameObject.h"
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

GameObject::GameObject(){
	
}

GameObject::GameObject(GameObjectConstructionInfo* _constructionInfo) : GameObject(){
	if (_constructionInfo->transform != nullptr) setTransform(_constructionInfo->transform);
	if (_constructionInfo->collider != nullptr) setCollider(_constructionInfo->collider);
	if (_constructionInfo->rigidbody != nullptr) setRigidbody(_constructionInfo->rigidbody);
	if (_constructionInfo->mesh != nullptr) setMesh(_constructionInfo->mesh);
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

Transform* GameObject::getTransform(){
	return transform;
}

Collider* GameObject::getCollider(){
	return collider;
}

Rigidbody* GameObject::getRigidbody(){
	return rigidbody;
}

MeshRenderer* GameObject::getMeshRenderer(){
	return meshRenderer;
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
	meshRenderer->gameObject = this;
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

void GameObject::setRigidbody(Rigidbody* _rigidbody){
	rigidbody = _rigidbody;
	rigidbody->gameObject = this;
	rigidbody->transform = transform;
}

/**
* OTHER METHODS
*/

void GameObject::attachGameObject(GameObject* _gameObject){
	children.push_back(_gameObject);
	_gameObject->parent = this;
}

void GameObject::Update(float _deltaTime){
	if (rigidbody != nullptr) rigidbody->Update(_deltaTime);
	for (size_t i = 0; i < children.size(); i++){
		children[i]->Update(_deltaTime);
	}
}

void GameObject::Draw(){
	if (meshRenderer != nullptr){
		meshRenderer->Render();
	}
}