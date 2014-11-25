#pragma once
#include "Collider.h"

class SphereCollider : public Collider{
private:
	float radius, scale;
public:
	SphereCollider();
	~SphereCollider();
	virtual float getScale();
	virtual void setScale(float _scaleAmt);
	virtual void setDimensions(float _width, float _height, float _length);
	virtual void setDimensions(float _radius);
};

