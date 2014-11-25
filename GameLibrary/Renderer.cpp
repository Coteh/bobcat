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
}

void Renderer::RenderObject(GameObject* _gameObject){
	if (shaderManager->getCurrShader() == nullptr || _gameObject->getShader()->shaderProgram != shaderManager->getCurrShader()->shaderProgram){
		shaderManager->useShader(_gameObject->getShader()->name);
	}
	if (_gameObject->getMesh()->getBoundShaderProgram() != _gameObject->getShader()->shaderProgram){
		shaderManager->updateAttribs(_gameObject->getShader()->name, _gameObject->getMesh());
		_gameObject->getMesh()->setBoundShaderProgram(shaderManager->getCurrShader()->shaderProgram);
	}
	glm::mat4 mvp = camera->getProjection() * camera->getView() * _gameObject->getModelMat();
	glUniformMatrix4fv(shaderManager->getCurrShader()->mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
	_gameObject->Draw();
	if (isDebugOn){
		Collider* col = _gameObject->getCollider();
		if (col != nullptr){
			float colScale = col->getScale();
			glUniformMatrix4fv(shaderManager->getCurrShader()->mvpLoc, 1, GL_FALSE, glm::value_ptr(glm::scale(mvp, glm::vec3(colScale, colScale, colScale))));
			_gameObject->DrawDebug();
		}
	}

	std::vector<GameObject*> childs = _gameObject->getChildren();
	for (int i = 0; i < childs.size(); i++){
		RenderObject(childs[i]);
	}
}

void Renderer::EndRender(){
	
}
