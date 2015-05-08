#include "Collider.h"

using namespace bobcat;

Collider::Collider(){

}

Collider::~Collider(){

}

glm::vec3 Collider::getPosition(){
	return m_position;
}

float Collider::getScale(){
	return m_scale;
}

float Collider::getRadius(){
	return NULL;
}

glm::vec3 Collider::getDimensions(){
	return glm::vec3(0.0f);
}

ColliderType Collider::getColliderType(){
	return m_colliderType;
}

void Collider::setPosition(glm::vec3 _pos){
	m_position = _pos;
}

void Collider::setScale(float _scaleAmt){
	m_scale = _scaleAmt;
}

void Collider::setColliderType(ColliderType _colliderType){
	m_colliderType = _colliderType;
}