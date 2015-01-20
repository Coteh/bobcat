#include "Rigidbody.h"
#include "GameObject.h"

using namespace bobcat;

Rigidbody::Rigidbody() {
	m_velocity = glm::vec3(0.0f);
	m_rotationalVel = glm::vec3(0.0f);
	m_friction = 1.0f;
}

Rigidbody::~Rigidbody() {
}

glm::vec3 Rigidbody::getVelocity(){
	return m_velocity;
}

glm::vec3 Rigidbody::getRotationalVel(){
	return m_rotationalVel;
}

glm::vec3 Rigidbody::getForce(){
	return m_force;
}

float Rigidbody::getFriction(){
	return m_friction;
}

void Rigidbody::setVelocity(glm::vec3 _vel){
	m_velocity = _vel;
}

void Rigidbody::setRotationalVel(glm::vec3 _rotVel){
	m_rotationalVel = _rotVel;
}

void Rigidbody::setForce(glm::vec3 _force){
	m_force = _force;
}

void Rigidbody::setFriction(float _fric){
	m_friction = _fric;
}

void Rigidbody::Update(float _deltaTime){
	if (gameObject->transform != nullptr){
		gameObject->transform->position += m_velocity * _deltaTime;
		gameObject->transform->Rotate(m_rotationalVel * _deltaTime);
	}
	m_velocity *= m_friction;
}