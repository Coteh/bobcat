#include "Camera.h"


Camera::Camera() {
	screenWidth = 1.0f;
	screenHeight = 1.0f;
	view = glm::mat4();
	projection = glm::mat4();
	zoom = 10.0f;
	position = glm::vec3(0, 0, 20);
}


Camera::~Camera() {

}

glm::mat4 Camera::getView(){
	return view;
}

glm::mat4 Camera::getProjection(){
	return projection;
}

void Camera::setCameraScreenDimensions(int _width, int _height){
	screenWidth = _width;
	screenHeight = _height;
}

void Camera::setZoom(float _zoom){
	zoom = _zoom;
	UpdateProjection();
}
void Camera::IncrementZoom(float _zoom){
	zoom += _zoom;
	UpdateProjection();
}

void Camera::UpdateCamera(){
	glm::vec3 eye = position; //the evil eye
	glm::vec3 direction = { 0.0f, 0.0f, -1.0f };
	glm::vec3 up = { 0.0f, 1.0f, 0.0f };
	view = glm::lookAt(eye, eye + direction, up);
}

void Camera::UpdateProjection(){
	projection = glm::perspective(zoom, 1.0f*screenWidth / screenHeight, 0.1f, 100.0f);
}
