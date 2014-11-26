#pragma once
#include "Collider.h"

class SphereCollider : public Collider{
private:
	float radius;
public:
	SphereCollider();
	~SphereCollider();
	virtual float getRadius();
	virtual void setDimensions(float _radius);
};

