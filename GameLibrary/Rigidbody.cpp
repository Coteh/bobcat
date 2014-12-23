#include "Rigidbody.h"

Rigidbody::Rigidbody() {
	velocity = glm::vec3(0.0f);
	rotationalVel = glm::vec3(0.0f);
	friction = 1.0f;
}

Rigidbody::~Rigidbody() {
}

void Rigidbody::Update(float _deltaTime){
	if (transform != nullptr){
		transform->position += velocity * _deltaTime;
		transform->rotation += rotationalVel * _deltaTime;
	}
	velocity *= friction;
}