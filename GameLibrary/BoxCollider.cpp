#include "BoxCollider.h"

BoxCollider::BoxCollider() {
	width = 0;
	height = 0;
	length = 0;
	drawType = ColliderDebugDrawType::BOX;
}

BoxCollider::~BoxCollider() {
}

void BoxCollider::setDimensions(float _width, float _height, float _length){
	width = _width;
	height = _height;
	length = _length;
}