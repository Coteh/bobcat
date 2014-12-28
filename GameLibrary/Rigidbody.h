#pragma once
#include <glm\glm.hpp>
#include "Component.h"
#include "Transform.h"

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

