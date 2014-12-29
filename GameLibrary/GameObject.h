#pragma once

#include <map>
#include <typeindex>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Component.h"
#include "Mesh.h"
#include "TextureLoader.h"

#include "Transform.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "MeshRenderer.h"

#include "ComponentHolder.h"

class GameObject {
private:
	GameObject* parent;
	std::vector<GameObject*> children;
	std::string name;
	ComponentHolder* componentHolder;

	void AddComponent(Component* _component, std::type_index _index);
public:
	GameObject();

	~GameObject();

	std::vector<GameObject*> getChildren();

	std::string getName();

	glm::mat4 getModelMat();

	void setName(std::string _name);

	void setMesh(Mesh* _mesh);

	void attachGameObject(GameObject* _gameObject);

	template <typename T>
	T* AddComponent();

	template <typename T>
	T* GetComponent();

	template <typename T>
	void RemoveComponent();

	void RemoveAllComponents();

	void Update(float _deltaTime);

	void Draw();

	Transform* transform;
	Collider* collider;
	Rigidbody* rigidbody;
	MeshRenderer* renderer;
	bool isWireFrameOn;
};

template <typename T>
T* GameObject::AddComponent() {
	//static_assert(std::is_base_of<Component, T>(), "This is not a component, cannot add it to GameObject");
	T* com = new T();
	std::type_index index(typeid(com));
	AddComponent(com, typeid(com));
	return com;
}

template <typename T>
T* GameObject::GetComponent() {
	if (componentHolder == nullptr) return nullptr;
	return (T*)componentHolder->GetComponent(_name);
}

template <typename T>
void GameObject::RemoveComponent() {
	if (componentHolder == nullptr) return;
	componentHolder->RemoveComponent(typeid(T*));
}