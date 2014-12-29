#include "GameObject.h"
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

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
	renderer = AddComponent<MeshRenderer>();
	renderer->mesh = _mesh;
	renderer->CalibrateMeshData();
	renderer->isEnabled = true;
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
	_gameObject->parent = this;
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