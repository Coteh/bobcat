#pragma once
#include "Component.h"
#include <glm\glm.hpp>

class Transform : public Component {
private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::vec3 m_forward;
	glm::vec3 m_up;
	glm::vec3 m_right;

	void determineDirections();
public:
	Transform();
	~Transform();

	glm::vec3 getPosition();
	glm::vec3 getRotation();
	glm::vec3 getScale();
	glm::vec3 getForward();
	glm::vec3 getUp();
	glm::vec3 getRight();

	void setPosition(glm::vec3 _pos);
	void setRotation(glm::vec3 _rot);
	void setScale(glm::vec3 _sca);
	void setForward(glm::vec3 _fwd);
	void setUp(glm::vec3 _up);
	void setRight(glm::vec3 _rgt);

	__declspec(property(get = getPosition, put = setPosition)) glm::vec3 position;
	__declspec(property(get = getRotation, put = setRotation)) glm::vec3 rotation;
	__declspec(property(get = getScale, put = setScale)) glm::vec3 scale;
	__declspec(property(get = getForward, put = setForward)) glm::vec3 forward;
	__declspec(property(get = getUp, put = setUp)) glm::vec3 up;
	__declspec(property(get = getRight, put = setRight)) glm::vec3 right;
};

