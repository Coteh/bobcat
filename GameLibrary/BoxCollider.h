#pragma once
#include "Collider.h"

class BoxCollider : public Collider{
private:
	float width, height, length, scale;
public:
	BoxCollider();
	~BoxCollider();
	virtual float getScale();
	virtual void setScale(float _scaleAmt);
	virtual void setDimensions(float _width, float _height, float _length);
	virtual void setDimensions(float _radius);
};

