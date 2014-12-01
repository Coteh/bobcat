#pragma once
#include <glm\glm.hpp>

enum ColliderDebugDrawType{
	NONE = 0,
	BOX = 1,
	SPHERE = 2
};

class ICollider {
public:
	virtual ~ICollider(){};
	virtual glm::vec3 getPosition() = 0;
	virtual float getScale() = 0;
	virtual float getRadius() = 0;
	virtual ColliderDebugDrawType getDebugDrawType() = 0;
	virtual void setPosition(glm::vec3 _pos) = 0;
	virtual void setScale(float _scaleAmt) = 0;
	virtual void setDimensions(float _width, float _height, float _length) = 0;
	virtual void setDimensions(float _radius) = 0;
	virtual void setDebugDrawType(ColliderDebugDrawType _drawType) = 0;
};