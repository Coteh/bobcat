#include "SphereCollider.h"

SphereCollider::SphereCollider() {
}

SphereCollider::~SphereCollider() {
}

float SphereCollider::getScale(){
	return scale;
}

void SphereCollider::setScale(float _scaleAmt){
	scale = _scaleAmt;
}

void SphereCollider::setDimensions(float _width, float _height, float _length){

}

void SphereCollider::setDimensions(float _radius){

}