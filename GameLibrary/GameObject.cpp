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

	AddComponent(meshRenderer);
	//iterate through all components and set the meshrenderer of each to this
	ComponentMap::iterator it = componentHolder->getBegin();
	for (it; it != componentHolder->getEnd(); ++it){
		it->second->renderer = meshRenderer;
	}

	meshRenderer->mesh = _mesh;
	meshRenderer->CalibrateMeshData();
	meshRenderer->isEnabled = true;
}

void GameObject::setTransform(Transform* _transform){
	AddComponent(_transform);
	transform = _transform;
	//iterate through all components and set the transform of each to this
	ComponentMap::iterator it = componentHolder->getBegin();
	for (it; it != componentHolder->getEnd(); ++it){
		it->second->transform = _transform;
	}
}

void GameObject::setCollider(Collider* _collider){
	AddComponent(_collider);
	collider = _collider;
	//iterate through all components and set the collider of each to this
	ComponentMap::iterator it = componentHolder->getBegin();
	for (it; it != componentHolder->getEnd(); ++it){
		it->second->collider = _collider;
	}
}

void GameObject::setRigidbody(Rigidbody* _rigidbody){
	AddComponent(_rigidbody);
	rigidbody = _rigidbody;
	//iterate through all components and set the rigidbody of each to this
	ComponentMap::iterator it = componentHolder->getBegin();
	for (it; it != componentHolder->getEnd(); ++it){
		it->second->rigidbody = _rigidbody;
	}
}

/**
* OTHER METHODS
*/

void GameObject::attachGameObject(GameObject* _gameObject){
	children.push_back(_gameObject);
	_gameObject->parent = this;
}

void GameObject::AddComponent(Component* _component){
	if (componentHolder == nullptr){
		componentHolder = new ComponentHolder();
	}
	componentHolder->AddComponent(_component);
	_component->gameObject = this;
	_component->transform = transform;
	_component->collider = collider;
	_component->rigidbody = rigidbody;
	_component->renderer = meshRenderer;
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