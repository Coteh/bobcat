#pragma once
#include "Component.h"
#include <glm\glm.hpp>

enum ColliderDebugDrawType{
	NONE = 0,
	BOX = 1,
	SPHERE = 2
};

class Collider : public Component {
private:
	glm::vec3 m_position;
	float m_scale;
protected:
	ColliderDebugDrawType drawType;
public:
	Collider();
	virtual ~Collider();
	virtual glm::vec3 getPosition();
	virtual float getScale();
	virtual float getRadius();
	virtual glm::vec3 getDimensions();
	virtual ColliderDebugDrawType getDebugDrawType();
	virtual void setPosition(glm::vec3 _pos);
	virtual void setScale(float _scaleAmt);
	virtual void setRadius(float _radius){};
	virtual void setDimensions(float _width, float _height, float _length){};
	virtual void setDimensions(glm::vec3 _dim){};
	virtual void setDebugDrawType(ColliderDebugDrawType _drawType);

	__declspec(property(get = getPosition, put = setPosition)) glm::vec3 position;
	__declspec(property(get = getRadius, put = setRadius)) float radius;
	__declspec(property(get = getScale, put = setScale)) float scale;
};