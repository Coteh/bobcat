#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtc\type_ptr.hpp>

class Camera {
private:
	glm::mat4 view;
	glm::mat4 projection;
	glm::vec3 position;
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
};

