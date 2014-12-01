#pragma once
#include "Collider.h"

class SphereCollider : public Collider{
private:
	float radius;
public:
	SphereCollider();
	~SphereCollider();
	virtual float getRadius();
	virtual glm::vec3 getDimensions();
	virtual void setRadius(float _radius);
};

