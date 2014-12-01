#include "BoxCollider.h"

BoxCollider::BoxCollider() {
	width = 0;
	height = 0;
	length = 0;
	drawType = ColliderDebugDrawType::BOX;
}

BoxCollider::~BoxCollider() {
}

glm::vec3 BoxCollider::getDimensions(){
	return glm::vec3(width, height, length);
}

void BoxCollider::setDimensions(float _width, float _height, float _length){
	setDimensions(glm::vec3(_width, _height, _length));
}

void BoxCollider::setDimensions(glm::vec3 _dim){
	width = _dim.x;
	height = _dim.y;
	length = _dim.z;
}