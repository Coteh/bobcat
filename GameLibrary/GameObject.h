#pragma once

#include <map>
//#include <typeinfo>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Component.h"
#include "Mesh.h"
#include "Collider.h"
#include "TextureLoader.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "MeshRenderer.h"
#include "GameObjectConstructionInfo.h"
#include "ComponentHolder.h"

class GameObject {
private:
	GameObject* parent;
	std::vector<GameObject*> children;
	std::string name;
	Transform* transform;
	Rigidbody* rigidbody;
	Collider* collider;
	MeshRenderer* meshRenderer;
	ComponentHolder* componentHolder;
public:
	GameObject();

	GameObject(GameObjectConstructionInfo* _constructionInfo);

	~GameObject();

	std::vector<GameObject*> getChildren();

	std::string getName();

	glm::mat4 getModelMat();

	Transform* getTransform();

	Collider* getCollider();

	Rigidbody* getRigidbody();

	MeshRenderer* getMeshRenderer();

	void setName(std::string _name);

	void setMesh(Mesh* _mesh);

	void setTransform(Transform* _transform);

	void setCollider(Collider* _collider);

	void setRigidbody(Rigidbody* _rigidbody);

	void attachGameObject(GameObject* _gameObject);

	template <typename T>
	T* AddComponent();

	void AddComponent(Component* _component);

	void Update(float _deltaTime);

	void Draw();

	bool isWireFrameOn;
};

template <typename T>
T* GameObject::AddComponent(){
	//static_assert(std::is_base_of<Component, T>(), "This is not a component, cannot add it to GameObject");
	T* com = new T();
	AddComponent(com);
	return com;
}