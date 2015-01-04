#include "Transform.h"

Transform::Transform() {
	m_position = glm::vec3(0.0f);
	m_rotation = glm::vec3(0.0f);
	m_scale = glm::vec3(1.0f);
	m_forward = glm::vec3(0.0f, 0.0f, 1.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_right = glm::vec3(1.0f, 0.0f, 0.0f);
}

Transform::~Transform() {

}

glm::vec3 Transform::getPosition(){
	return m_position;
}

glm::vec3 Transform::getRotation(){
	return m_rotation;
}

glm::vec3 Transform::getScale(){
	return m_scale;
}

glm::vec3 Transform::getForward(){
	return m_forward;
}

glm::vec3 Transform::getUp(){
	return m_up;
}

glm::vec3 Transform::getRight(){
	return m_right;
}

void Transform::setPosition(glm::vec3 _pos){
	m_position = _pos;
}

void Transform::setRotation(glm::vec3 _rot){
	m_rotation = _rot;
	determineDirections();
}

void Transform::setScale(glm::vec3 _sca){
	m_scale = _sca;
}

void Transform::setForward(glm::vec3 _fwd){
	m_forward = _fwd;
}

void Transform::setUp(glm::vec3 _up){
	m_up = _up;
}

void Transform::setRight(glm::vec3 _rgt){
	m_right = _rgt;
}

void Transform::determineDirections(){
	float cosPitch = cos(glm::radians(rotation.x));
	float sinPitch = sin(glm::radians(rotation.x));
	float cosYaw = cos(glm::radians(rotation.y));
	float sinYaw = sin(glm::radians(rotation.y));

	right = { cosYaw, 0, -sinYaw }; //x axis
	up = { sinYaw * sinPitch, cosPitch, cosYaw * sinPitch }; //y axis
	forward = { sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw }; //z axis
}