#include "Camera.h"
#include "GameObject.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtc\type_ptr.hpp>

using namespace bobcat;

Camera::Camera() {
	screenWidth = 1.0f;
	screenHeight = 1.0f;
	view = glm::mat4();
	projection = glm::mat4();
	zoom = 10.0f;
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
	float zFor = (gameObject->transform != nullptr) ? gameObject->transform->forward.z : 1.0f;
	float zoomDir = (zFor / ::abs(zFor));
	if (zoomDir == 0) zoomDir = 1.0f;
	zoom += _zoom * zoomDir;
	UpdateProjection();
}

/**
* Update the Camera's View Matrix
* Thank you Jake for the help!
*/
void Camera::UpdateCamera(){
	//We need the game object's transform for its position and rotation
	Transform* transform = gameObject->transform;
	//If it isn't there, make view an identity matrix and exit
	if (transform == nullptr){
		view = glm::mat4(1.0f);
		return;
	}

	//Setup the 4x4 view matrix using the right, up, forward, and eye (position) vectors
	view = {
		transform->right.x, transform->up.x, transform->forward.x, 0,
		transform->right.y, transform->up.y, transform->forward.y, 0,
		transform->right.z, transform->up.z, transform->forward.z, 0,
		-glm::dot(transform->right, transform->position), -glm::dot(transform->up, transform->position), -glm::dot(transform->forward, transform->position), 1
	};
}

void Camera::UpdateProjection(){
	projection = glm::perspective(zoom, 1.0f*screenWidth / screenHeight, 0.1f, 1000.0f);
}

void Camera::Update(float _deltaTime){
	UpdateCamera();
}