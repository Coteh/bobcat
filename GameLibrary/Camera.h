#pragma once
#include "Component.h"
#include <glm\glm.hpp>

class Camera : public Component {
private:
	glm::mat4 view;
	glm::mat4 projection;
	int screenWidth, screenHeight;
	float zoom;
public:
	Camera();
	~Camera();
	glm::mat4 getView();
	glm::mat4 getProjection();
	void setCameraScreenDimensions(int _width, int _height);
	void setZoom(float _zoom);
	void IncrementZoom(float _zoom);
	void UpdateCamera();
	void UpdateProjection();
	virtual void Update(float _deltaTime);
};

