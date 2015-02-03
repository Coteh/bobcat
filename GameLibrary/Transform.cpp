#include "Transform.h"
#include <glm\gtx\rotate_vector.hpp>

using namespace bobcat;

Transform::Transform() {
	m_position = glm::vec3(0.0f);
	ResetOrientation();
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

//glm::vec3 Transform::getRotation(){
//	return m_rotation;
//}

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

glm::mat4 Transform::getOrientation() {
	return m_orientation;
}

void Transform::setPosition(glm::vec3 _pos){
	m_position = _pos;
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

void Transform::Rotate(glm::vec3 _euler) {
	m_orientation = glm::rotate(m_orientation, _euler.x, glm::vec3(1, 0, 0));
	m_orientation = glm::rotate(m_orientation, _euler.y, glm::vec3(0, 1, 0));
	m_orientation = glm::rotate(m_orientation, _euler.z, glm::vec3(0, 0, 1));

	m_rotation += _euler;
	
	determineDirections();
}

void Transform::ResetOrientation() {
	m_rotation = glm::vec3(0.0f);
	m_orientation = glm::mat4(1.0f);
	determineDirections();
}

void Transform::determineDirections(){
	float cosPitch = cos(glm::radians(m_rotation.x));
	float sinPitch = sin(glm::radians(m_rotation.x));
	float cosYaw = cos(glm::radians(m_rotation.y));
	float sinYaw = sin(glm::radians(m_rotation.y));

	right = { cosYaw, 0, -sinYaw }; //x axis
	up = { sinYaw * sinPitch, cosPitch, cosYaw * sinPitch }; //y axis
	forward = { sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw }; //z axis
}