#include "Collider.h"

Collider::Collider(){

}

Collider::~Collider(){

}

glm::vec3 Collider::getPosition(){
	return position;
}

float Collider::getScale(){
	return scale;
}

float Collider::getRadius(){
	return NULL;
}

glm::vec3 Collider::getDimensions(){
	return glm::vec3(0.0f);
}

ColliderDebugDrawType Collider::getDebugDrawType(){
	return drawType;
}

void Collider::setPosition(glm::vec3 _pos){
	position = _pos;
}

void Collider::setScale(float _scaleAmt){
	scale = _scaleAmt;
}

void Collider::setDebugDrawType(ColliderDebugDrawType _drawType){
	drawType = _drawType;
}