#include "Renderer.h"
#include "ResourceManager.h"
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

Renderer::Renderer() {
	
}

Renderer::~Renderer() {
}

void Renderer::Init(){
	shaderManager = ShaderManager::getInstance();
	ResourceManager* resourceManager = ResourceManager::getInstance();
	resourceManager->addMesh("Cube.ply", "Debug_ColliderBox");
	resourceManager->addMesh("Sphere.ply", "Debug_ColliderSphere");
	boxColliderMesh = resourceManager->getMesh("Debug_ColliderBox");
	sphereColliderMesh = resourceManager->getMesh("Debug_ColliderSphere");
	ShaderLoadInfo debugShaderInfo[] = {
		{ GL_VERTEX_SHADER, "debug-vert.glsl" },
		{ GL_FRAGMENT_SHADER, "debug-frag.glsl" },
		{ GL_NONE, NULL }
	};
	shaderManager->addShader(ShaderLoader::LoadShaders(debugShaderInfo), "DebugShader");
	debugShader = shaderManager->getShader("DebugShader");
}

void Renderer::setActiveCamera(Camera* _camera){
	activeCamera = _camera;
}

void Renderer::PreRender(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::RenderObject(GameObject* _gameObject){
	/*Drawing GameObject*/
	if (_gameObject->getShader() != nullptr){ //don't draw if shader is null
		if (shaderManager->getCurrShader() == nullptr || _gameObject->getShader()->shaderProgram != shaderManager->getCurrShader()->shaderProgram){
			shaderManager->useShader(_gameObject->getShader()->name);
		}
		if (_gameObject->getMesh() != nullptr){ //don't draw if mesh is null
			if (_gameObject->getMesh()->getBoundShaderProgram() != _gameObject->getShader()->shaderProgram){
				shaderManager->updateAttribs(_gameObject->getShader()->name, _gameObject->getMesh());
				_gameObject->getMesh()->setBoundShaderProgram(shaderManager->getCurrShader()->shaderProgram);
			}
			glUniform4fv(shaderManager->getCurrShader()->colorLoc, 1, glm::value_ptr(_gameObject->getColor()));
			glm::mat4 mvp = activeCamera->getProjection() * activeCamera->getView() * _gameObject->getModelMat();
			glUniformMatrix4fv(shaderManager->getCurrShader()->mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
			if (_gameObject->getTexture() != nullptr){
				_gameObject->getTexture()->Bind(shaderManager->getCurrShader()->texSamplerLoc);
			}
			_gameObject->Draw();
			glBindTexture(GL_TEXTURE_2D, 0);

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
					shaderManager->useShader(debugShader->name);
					if (colMesh->getBoundShaderProgram() != debugShader->shaderProgram){
						shaderManager->updateAttribs(debugShader->name, colMesh);
						colMesh->setBoundShaderProgram(debugShader->shaderProgram);
					}
					float colScale = col->getScale();
					glm::vec3 dimensions = col->getDimensions();
					//Let's just assume the collider position is always with the GameObject's position... hehehe :P
					//so just use the GameObject's MVP and not make a new matrix with its translation
					glm::mat4 debugMat = glm::scale(mvp, glm::vec3(colScale * dimensions.x, colScale * dimensions.y, colScale * dimensions.z));
					glUniformMatrix4fv(debugShader->mvpLoc, 1, GL_FALSE, glm::value_ptr(debugMat));
					RenderDebugMesh(colMesh);
				}
			}
		}
	}

	/*Drawing children*/
	std::vector<GameObject*> childs = _gameObject->getChildren();
	for (size_t i = 0; i < childs.size(); i++){
		RenderObject(childs[i]);
	}
}

void Renderer::RenderDebugMesh(Mesh* _mesh){
	glBindVertexArray(_mesh->getVAO());
	std::vector<int> indiceCountData =_mesh->getIndiceCountData();
	std::vector<GLenum> drawModeVec = _mesh->getDrawModes();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	int indicesSoFar = 0;
	for (size_t i = 0; i < drawModeVec.size(); i++){
		glDrawElements(drawModeVec[i], indiceCountData[i], GL_UNSIGNED_INT, (void*)(indicesSoFar * sizeof(GLuint)));
		indicesSoFar += indiceCountData[i];
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(0);
}

void Renderer::EndRender(){
	
}
