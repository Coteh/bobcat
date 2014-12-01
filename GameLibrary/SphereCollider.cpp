#include "SphereCollider.h"

SphereCollider::SphereCollider() {
	radius = 1.0f;
	drawType = ColliderDebugDrawType::SPHERE;
}

SphereCollider::~SphereCollider() {
}

float SphereCollider::getRadius(){
	return radius;
}

glm::vec3 SphereCollider::getDimensions(){
	return glm::vec3(radius, radius, radius);
}

void SphereCollider::setRadius(float _radius){
	radius = _radius;
}