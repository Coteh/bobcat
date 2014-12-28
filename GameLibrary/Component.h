#pragma once
#include <string>

class GameObject;
class Transform;
class Collider;
class Rigidbody;
class MeshRenderer;

class Component {
public:
	Component(){}
	~Component(){}

	std::string name;

	GameObject* gameObject;
	Transform* transform;
	Collider* collider;
	Rigidbody* rigidbody;
	MeshRenderer* renderer;

	virtual void Update(float _deltaTime){}
};