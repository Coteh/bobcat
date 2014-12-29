#pragma once
#include <string>

class GameObject;

class Component {
public:
	Component(){}
	~Component(){}

	GameObject* gameObject;

	virtual void Update(float _deltaTime){}
};