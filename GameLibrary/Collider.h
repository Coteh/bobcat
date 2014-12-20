#pragma once
#include <glm\glm.hpp>

enum ColliderDebugDrawType{
	NONE = 0,
	BOX = 1,
	SPHERE = 2
};

class GameObject;
class Transform;

class Collider {
private:
	glm::vec3 position;
	float scale;
protected:
	ColliderDebugDrawType drawType;
public:
	Collider();
	virtual ~Collider();
	GameObject* gameObject;
	Transform* transform;
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
};