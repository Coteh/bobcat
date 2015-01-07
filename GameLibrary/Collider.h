#pragma once
#include "Component.h"
#include <glm\glm.hpp>

enum ColliderDebugDrawType{
	NONE = 0,
	BOX = 1,
	SPHERE = 2
};

/**
* The base class of all colliders.
* Gives a GameObject a bounding space.
*/
class Collider : public Component {
private:
	glm::vec3 m_position;
	float m_scale;
protected:
	ColliderDebugDrawType drawType;
public:
	Collider();
	virtual ~Collider();

	/**
	* Get collider position.
	* @note This is used in the position property and can also be called from there.
	* @return Position represented as a Vector3.
	*/
	virtual glm::vec3 getPosition();

	/**
	* Get collider scale.
	* @note This is used in the scale property and can also be called from there.
	* @return Scale represented as a float.
	*/
	virtual float getScale();

	/**
	* Get collider radius.
	* @note This is used in the radius property and can also be called from there.
	* @return Radius of the collider for spherical colliders. NULL if collider shape doesn't have a radius.
	*/
	virtual float getRadius();

	/**
	* Get collider dimensions.
	* @return Vector3 of width, height, and length respectively.
	*/
	virtual glm::vec3 getDimensions();

	/**
	* Get the type of collider shape this collider will render. (will only render if debug draw is turned on)
	* @return ColliderDebugDrawType enum value representing the type of shape it will draw.
	*/
	virtual ColliderDebugDrawType getDebugDrawType();

	/**
	* Set position of the collider.
	* @note This is used in the position property and can also be called from there.
	* @param _pos Position represented as a Vector3.
	*/
	virtual void setPosition(glm::vec3 _pos);

	/**
	* Set the collider's scale.
	* @note This is used in the scale property and can also be called from there.
	* @param _scaleAmt Scale represented as a float.
	*/
	virtual void setScale(float _scaleAmt);

	/**
	* Set the collider's radius.
	* @note This is used in the radius property and can also be called from there.
	* @param _radius Radius of the collider for spherical colliders.
	*/
	virtual void setRadius(float _radius){};

	/**
	* Set the collider's dimensions.
	* @param _width A float representing width.
	* @param _height A float representing height.
	* @param _length A float representing length.
	*/
	virtual void setDimensions(float _width, float _height, float _length){};

	/**
	* Set the collider's dimensions.
	* @param _dim Vector3 of width, height, and length respectively.
	*/
	virtual void setDimensions(glm::vec3 _dim){};

	/**
	* Set the type of collider shape this collider will render. (will only render if debug draw is turned on)
	* @param _drawType ColliderDebugDrawType enum value representing the type of shape it will draw.
	*/
	virtual void setDebugDrawType(ColliderDebugDrawType _drawType);

	/**
	* Property to access the position of the Collider.
	*/
	__declspec(property(get = getPosition, put = setPosition)) glm::vec3 position;

	/**
	* Property to access the radius of the Collider.
	*/
	__declspec(property(get = getRadius, put = setRadius)) float radius;

	/**
	* Property to access the scale of the Collider.
	*/
	__declspec(property(get = getScale, put = setScale)) float scale;
};