#include "BoxCollider.h"

BoxCollider::BoxCollider() {
	m_width = 0;
	m_height = 0;
	m_length = 0;
	drawType = ColliderDebugDrawType::BOX;
}

BoxCollider::~BoxCollider() {
}

float BoxCollider::getWidth() {
	return m_width;
}

float BoxCollider::getHeight() {
	return m_height;
}

float BoxCollider::getLength() {
	return m_length;
}

glm::vec3 BoxCollider::getDimensions(){
	return glm::vec3(m_width, m_height, m_length);
}

void BoxCollider::setWidth(float _width){
	m_width = _width;
}

void BoxCollider::setHeight(float _height){
	m_height = _height;
}

void BoxCollider::setLength(float _length){
	m_length = _length;
}

void BoxCollider::setDimensions(float _width, float _height, float _length){
	setDimensions(glm::vec3(_width, _height, _length));
}

void BoxCollider::setDimensions(glm::vec3 _dim){
	setWidth(_dim.x);
	setHeight(_dim.y);
	setLength(_dim.z);
}