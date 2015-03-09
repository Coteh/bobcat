#include "GameObject.h"
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

using namespace bobcat;

GameObject::GameObject(){

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
		model *= transform->orientation;
		model = glm::scale(model, transform->scale);
	}
	if (m_parent && relativeTo == RELATIVE_TO::PARENT){
		model = m_parent->getModelMat() * model;
	}
	return model;
}

GameObject* GameObject::getParent() {
	return m_parent;
}

/**
* SET METHODS
*/

void GameObject::setName(std::string _name){
	name = _name;
}

void GameObject::setParent(GameObject* _parent){
	m_parent = _parent;
}

/**
* COMPONENT METHODS
*/

void GameObject::AddComponent(Component* _component, std::type_index _index){
	if (componentHolder == nullptr){
		componentHolder = new ComponentHolder();
	}
	componentHolder->AddComponent(_component, _index);
	_component->gameObject = this;
}

void GameObject::RemoveAllComponents(){
	if (componentHolder == nullptr) return;
	componentHolder->RemoveAll();
}

/**
* OTHER METHODS
*/

void GameObject::attachGameObject(GameObject* _gameObject){
	children.push_back(_gameObject);
	_gameObject->setParent(this);
}

void GameObject::Update(float _deltaTime){
	//Update all the Components
	if (componentHolder != nullptr){
		ComponentMap::iterator it = componentHolder->getBegin();
		for (it; it != componentHolder->getEnd(); ++it){
			it->second->Update(_deltaTime);
		}
	}
	//Update children
	for (size_t i = 0; i < children.size(); i++){
		children[i]->Update(_deltaTime);
	}
}

void GameObject::Draw(){
	if (renderer != nullptr){
		renderer->Render();
	}
}