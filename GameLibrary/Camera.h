#pragma once
#include "Component.h"
#include <glm\glm.hpp>

class Camera : public Component {
private:
	glm::mat4 view;
	glm::mat4 projection;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 rotation;
	glm::vec3 right;
	int screenWidth, screenHeight;
	float zoom;
public:
	Camera();
	~Camera();
	glm::mat4 getView();
	glm::mat4 getProjection();
	glm::vec3 getPosition();
	glm::vec3 getRotationEuler();
	glm::vec3 getForward();
	glm::vec3 getRight();
	glm::vec3 getUp();
	void setCameraScreenDimensions(int _width, int _height);
	void setZoom(float _zoom);
	void setPosition(glm::vec3 _position);
	void setRotationEuler(glm::vec3 _rot);
	void IncrementZoom(float _zoom);
	void Translate(glm::vec3 _offset);
	void Rotate(glm::vec3 _rotEuler);
	void UpdateCamera();
	void UpdateProjection();
	virtual void Update(float _deltaTime);
};

