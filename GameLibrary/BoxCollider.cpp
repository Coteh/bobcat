#include "BoxCollider.h"

BoxCollider::BoxCollider() {
}

BoxCollider::~BoxCollider() {
}

float BoxCollider::getScale(){
	return scale;
}

void BoxCollider::setScale(float _scaleAmt){
	scale = _scaleAmt;
}

void BoxCollider::setDimensions(float _width, float _height, float _length){
	
}

void BoxCollider::setDimensions(float _radius){

}