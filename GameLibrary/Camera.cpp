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
	position = glm::vec3(0, 0, 0);
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
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

glm::vec3 Camera::getRotationEuler(){
	return rotation;
}

glm::vec3 Camera::getForward(){
	return forward;
}

glm::vec3 Camera::getRight(){
	return right;
}

glm::vec3 Camera::getUp(){
	return up;
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

void Camera::setRotationEuler(glm::vec3 _rot){
	rotation = _rot;
	UpdateCamera();
}

void Camera::attachGameObject(GameObject* _gameObject){
	attachedGameObject = _gameObject;
}

void Camera::IncrementZoom(float _zoom){
	float zoomDir = (forward.z / ::abs(forward.z));
	if (zoomDir == 0) zoomDir = 1.0f;
	zoom += _zoom * zoomDir;
	UpdateProjection();
}

void Camera::Translate(glm::vec3 _offset){
	position += _offset;
	UpdateCamera();
}

void Camera::Rotate(glm::vec3 _rotEuler){
	rotation += _rotEuler * up;
	UpdateCamera();
}

/**
* Update the Camera's View Matrix
* Thank you Jake for the help!
*/
void Camera::UpdateCamera(){
	float cosPitch = cos(glm::radians(rotation.x));
	float sinPitch = sin(glm::radians(rotation.x));
	float cosYaw = cos(glm::radians(rotation.y));
	float sinYaw = sin(glm::radians(rotation.y));

	right = { cosYaw, 0, -sinYaw }; //x axis
	up = { sinYaw * sinPitch, cosPitch, cosYaw * sinPitch }; //y axis
	forward = { sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw }; //z axis

	//Setup the 4x4 view matrix using the right, up, forward, and eye (position) vectors
	view = {
		right.x, up.x, forward.x, 0,
		right.y, up.y, forward.y, 0,
		right.z, up.z, forward.z, 0,
		-glm::dot(right, position), -glm::dot(up, position), -glm::dot(forward, position), 1
	};
}

void Camera::UpdateProjection(){
	projection = glm::perspective(zoom, 1.0f*screenWidth / screenHeight, 0.1f, 1000.0f);
}
