#include "Camera.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtc\type_ptr.hpp>

Camera::Camera() {
	screenWidth = 1.0f;
	screenHeight = 1.0f;
	view = glm::mat4();
	projection = glm::mat4();
	zoom = 10.0f;
	position = glm::vec3(0, 0, 20);
	direction = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
}


Camera::~Camera() {

}

glm::mat4 Camera::getView(){
	return view;
}

glm::mat4 Camera::getProjection(){
	return projection;
}

glm::vec3 Camera::getPosition(){
	return position;
}

glm::vec3 Camera::getDirection(){
	return direction;
}

void Camera::setCameraScreenDimensions(int _width, int _height){
	screenWidth = _width;
	screenHeight = _height;
}

void Camera::setZoom(float _zoom){
	zoom = _zoom;
	UpdateProjection();
}

void Camera::setPosition(glm::vec3 _position){
	position = _position;
	UpdateCamera();
}

void Camera::attachGameObject(GameObject* _gameObject){
	attachedGameObject = _gameObject;
}

void Camera::IncrementZoom(float _zoom){
	float zoomDir = (direction.z / ::abs(direction.z));
	if (zoomDir == 0) zoomDir = 1.0f;
	zoom += _zoom * zoomDir;
	UpdateProjection();
}

void Camera::Translate(glm::vec3 _offset){
	position += _offset;
	UpdateCamera();
}

void Camera::Rotate(glm::vec3 _rotEuler){
	/*direction = glm::rotate(direction, 0.16f, _rotEuler);
	UpdateCamera();*/
	rotation += _rotEuler;
	UpdateCamera();
}

void Camera::UpdateCamera(){
	//Thank you Jake!
	float cosPitch = cos(glm::radians(rotation.x));
	float sinPitch = sin(glm::radians(rotation.x));
	float cosYaw = cos(glm::radians(rotation.y));
	float sinYaw = sin(glm::radians(rotation.y));

	glm::vec3 xaxis = { cosYaw, 0, -sinYaw };
	glm::vec3 yaxis = { sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
	glm::vec3 zaxis = { sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw };

	// Create a 4x4 view matrix from the right, up, forward and eye position vectors
	view = {
		xaxis.x, yaxis.x, zaxis.x, 0,
		xaxis.y, yaxis.y, zaxis.y, 0,
		xaxis.z, yaxis.z, zaxis.z, 0,
		-glm::dot(xaxis, position), -glm::dot(yaxis, position), -glm::dot(zaxis, position), 1
	};
}

void Camera::UpdateProjection(){
	projection = glm::perspective(zoom, 1.0f*screenWidth / screenHeight, 0.1f, 100.0f);
}
