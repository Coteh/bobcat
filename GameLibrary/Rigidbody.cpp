#include "Rigidbody.h"
#include "GameObject.h"

Rigidbody::Rigidbody() {
	velocity = glm::vec3(0.0f);
	rotationalVel = glm::vec3(0.0f);
	friction = 1.0f;
}

Rigidbody::~Rigidbody() {
}

void Rigidbody::Update(float _deltaTime){
	if (gameObject->transform != nullptr){
		gameObject->transform->position += velocity * _deltaTime;
		gameObject->transform->rotation += rotationalVel * _deltaTime;
	}
	velocity *= friction;
}