#include "Renderer.h"


Renderer::Renderer() {
}


Renderer::~Renderer() {
}

void Renderer::Init(){
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "square.vert" },
		{ GL_FRAGMENT_SHADER, "square.frag" },
		{ GL_NONE, NULL }
	};

	program = ShaderManager::LoadShaders(shaders);
	glUseProgram(program);

	modelLoc = glGetUniformLocation(program, "Model");
	cameraLoc = glGetUniformLocation(program, "Camera");
	projectionLoc = glGetUniformLocation(program, "Perspective_Projection");
}

void Renderer::setCamera(Camera* _camera){
	camera = _camera;
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
