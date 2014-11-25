#include "Camera.h"


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
	direction += _rotEuler;
	UpdateCamera();
}

void Camera::UpdateCamera(){
	view = glm::lookAt(position, position + direction, up); //position is the evil eye!
}

void Camera::UpdateProjection(){
	projection = glm::perspective(zoom, 1.0f*screenWidth / screenHeight, 0.1f, 100.0f);
}
