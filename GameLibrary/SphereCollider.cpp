#include "SphereCollider.h"

SphereCollider::SphereCollider() {
	radius = 0;
	drawType = ColliderDebugDrawType::SPHERE;
}

SphereCollider::~SphereCollider() {
}

float SphereCollider::getRadius(){
	return radius;
}

void SphereCollider::setDimensions(float _radius){
	radius = _radius;
}