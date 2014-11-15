#include "Renderer.h"


Renderer::Renderer() {

}

Renderer::~Renderer() {
}

void Renderer::Init(){
	shaderManager = ShaderManager::getInstance();
}

void Renderer::setCamera(Camera* _camera){
	camera = _camera;
}

void Renderer::PreRender(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUniformMatrix4fv(shaderManager->getCurrShader()->cameraLoc, 1, GL_FALSE, glm::value_ptr(camera->getView()));
	glUniformMatrix4fv(shaderManager->getCurrShader()->projectionLoc, 1, GL_FALSE, glm::value_ptr(camera->getProjection()));
}

void Renderer::RenderObject(GameObject* _gameObject){
	_gameObject->Draw(shaderManager->getCurrShader()->modelLoc);
}

void Renderer::EndRender(){
	//glEnd();
}
