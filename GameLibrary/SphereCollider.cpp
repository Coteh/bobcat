#include "SphereCollider.h"

SphereCollider::SphereCollider() {
	m_radius = 1.0f;
	drawType = ColliderDebugDrawType::SPHERE;
}

SphereCollider::~SphereCollider() {
}

float SphereCollider::getRadius(){
	return m_radius;
}

glm::vec3 SphereCollider::getDimensions(){
	return glm::vec3(m_radius, m_radius, m_radius);
}

void SphereCollider::setRadius(float _radius){
	m_radius = _radius;
}