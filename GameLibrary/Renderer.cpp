#include "Renderer.h"


Renderer::Renderer() {
}


Renderer::~Renderer() {
}

void Renderer::Init(){
	
}

void Renderer::setCamera(Camera* _camera){
	camera = _camera;
}

void Renderer::SwitchShader(GLuint _program){
	glUseProgram(_program);
	UpdateLocations(_program);
}

void Renderer::UpdateLocations(GLuint _program){
	modelLoc = glGetUniformLocation(_program, "Model");
	cameraLoc = glGetUniformLocation(_program, "Camera");
	projectionLoc = glGetUniformLocation(_program, "Perspective_Projection");
}

void Renderer::PreRender(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniformMatrix4fv(cameraLoc, 1, GL_FALSE, glm::value_ptr(camera->getView()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera->getProjection()));
}

void Renderer::RenderObject(GameObject* _gameObject){
	_gameObject->Draw(modelLoc);
}

void Renderer::EndRender(){
	glEnd();
}
