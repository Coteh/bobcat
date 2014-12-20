#pragma once
#include "Collider.h"
#include <glm\glm.hpp>

class GameObject;

class Transform {
public:
	Transform();
	~Transform();
	GameObject* gameObject;
	Collider* collider;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

