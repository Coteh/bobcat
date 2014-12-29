#pragma once
#include "Component.h"
#include <glm\glm.hpp>

class Rigidbody : public Component {
public:
	Rigidbody();
	~Rigidbody();

	glm::vec3 velocity;
	glm::vec3 rotationalVel;
	glm::vec3 force;
	float friction;

	virtual void Update(float _deltaTime);
};

