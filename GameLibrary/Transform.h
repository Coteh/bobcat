#pragma once
#include "Component.h"
#include "Collider.h"
#include <glm\glm.hpp>

class Transform : public Component {
public:
	Transform();
	~Transform();

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

