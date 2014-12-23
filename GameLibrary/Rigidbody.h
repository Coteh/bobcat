#pragma once
#include <glm\glm.hpp>
#include "Transform.h"

class GameObject;

class Rigidbody {
public:
	Rigidbody();
	~Rigidbody();

	GameObject* gameObject;
	Transform* transform;

	glm::vec3 velocity;
	glm::vec3 rotationalVel;
	glm::vec3 force;
	float friction;

	void Update(float _deltaTime);
};

