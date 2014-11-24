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
	glm::vec3 direction;
	glm::vec3 up;
	int screenWidth, screenHeight;
	float zoom;
public:
	Camera();
	~Camera();
	glm::mat4 getView();
	glm::mat4 getProjection();
	glm::vec3 getPosition();
	void setCameraScreenDimensions(int _width, int _height);
	void setZoom(float _zoom);
	void setPosition(glm::vec3 _position);
	void IncrementZoom(float _zoom);
	void Translate(glm::vec3 _offset);
	void Rotate(glm::vec3 _rotEuler);
	void UpdateCamera();
	void UpdateProjection();
};

