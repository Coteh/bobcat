#pragma once
#include "ICollider.h"
#include <glm\glm.hpp>

class Collider : public ICollider {
private:
	glm::vec3 position;
	float scale;
protected:
	ColliderDebugDrawType drawType;
public:
	Collider();
	virtual ~Collider();
	virtual glm::vec3 getPosition();
	virtual float getScale();
	virtual float getRadius();
	virtual ColliderDebugDrawType getDebugDrawType();
	virtual void setPosition(glm::vec3 _pos);
	virtual void setScale(float _scaleAmt);
	virtual void setDimensions(float _width, float _height, float _length){};
	virtual void setDimensions(float _radius){};
	virtual void setDebugDrawType(ColliderDebugDrawType _drawType);
};