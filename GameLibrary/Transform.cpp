#include "Transform.h"

Transform::Transform() {
	name = "Transform";
	position = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
}

Transform::~Transform() {

}
