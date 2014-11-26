#include "Renderer.h"
#include "MeshManager.h"

Renderer::Renderer() {
	
}

Renderer::~Renderer() {
}

void Renderer::Init(){
	shaderManager = ShaderManager::getInstance();
	MeshManager* meshManager = MeshManager::getInstance();
	meshManager->addMesh("TestModel2.ply", "Debug_ColliderBox");
	meshManager->addMesh("Sphere.ply", "Debug_ColliderSphere");
	boxColliderMesh = meshManager->getMesh("Debug_ColliderBox");
	sphereColliderMesh = meshManager->getMesh("Debug_ColliderSphere");
}

void Renderer::setCamera(Camera* _camera){
	camera = _camera;
}

void Renderer::PreRender(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::RenderObject(GameObject* _gameObject){
	/*Drawing GameObject*/
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

	/*Drawing Debug stuff*/
	if (isDebugOn){
		Collider* col = _gameObject->getCollider();
		if (col != nullptr){
			Mesh* colMesh;
			if (col->getDebugDrawType() == ColliderDebugDrawType::SPHERE){
				colMesh = sphereColliderMesh;
			} else{
				colMesh = boxColliderMesh;
			}
			if (!colMesh->getBoundShaderProgram() != _gameObject->getShader()->shaderProgram){
				shaderManager->updateAttribs(_gameObject->getShader()->name, colMesh);
				colMesh->setBoundShaderProgram(shaderManager->getCurrShader()->shaderProgram);
			}
			float colScale = col->getScale();
			glm::mat4 debugMat = glm::translate(mvp, col->getPosition());
			debugMat = glm::scale(debugMat, glm::vec3(colScale, colScale, colScale));
			glUniformMatrix4fv(shaderManager->getCurrShader()->mvpLoc, 1, GL_FALSE, glm::value_ptr(debugMat));
			RenderDebugMesh(colMesh);
		}
	}

	/*Drawing children*/
	std::vector<GameObject*> childs = _gameObject->getChildren();
	for (int i = 0; i < childs.size(); i++){
		RenderObject(childs[i]);
	}
}

void Renderer::RenderDebugMesh(Mesh* _mesh){
	glBindVertexArray(_mesh->getVAO());
	std::vector<int> indiceCountData =_mesh->getIndiceCountData();
	std::vector<GLenum> drawModeVec = _mesh->getDrawModes();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	int indicesSoFar = 0;
	for (int i = 0; i < drawModeVec.size(); i++){
		glDrawElements(drawModeVec[i], indiceCountData[i], GL_UNSIGNED_INT, (void*)(indicesSoFar * sizeof(GLuint)));
		indicesSoFar += indiceCountData[i];
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(0);
}

void Renderer::EndRender(){
	
}
