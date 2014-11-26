#pragma once
#include "Collider.h"

class BoxCollider : public Collider{
private:
	float width, height, length;
public:
	BoxCollider();
	~BoxCollider();
	virtual void setDimensions(float _width, float _height, float _length);
};

