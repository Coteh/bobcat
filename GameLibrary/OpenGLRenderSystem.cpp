#include "OpenGLRenderSystem.h"
#include "ResourceManager.h"
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

OpenGLRenderSystem::OpenGLRenderSystem() {

}

OpenGLRenderSystem::~OpenGLRenderSystem() {
}

void OpenGLRenderSystem::Init(){
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

void OpenGLRenderSystem::setActiveCamera(Camera* _camera){
	activeCamera = _camera;
}

void OpenGLRenderSystem::setDebugRender(bool _expression){
	isDebugOn = _expression;
}

void OpenGLRenderSystem::PreRender(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderSystem::RenderObject(GameObject* _gameObject){
	/*Drawing GameObject*/
	if (_gameObject->getShader() != nullptr){ //don't draw if shader is null
		//Make sure OpenGL is always using the shader program that the GameObject is using
		if (shaderManager->getCurrShader() == nullptr || _gameObject->getShader()->shaderProgram != shaderManager->getCurrShader()->shaderProgram){
			shaderManager->useShader(_gameObject->getShader()->name);
		}
		//Calculate Model View Projection for the GameObject
		glm::mat4 mvp = activeCamera->getProjection() * activeCamera->getView() * _gameObject->getModelMat();
		if (_gameObject->getMeshRenderer()->mesh != nullptr){ //don't draw if mesh is null
			//Update Mesh attributes if the GameObject's shader is different than the one the mesh has at the moment
			if (_gameObject->getMeshRenderer()->mesh->getBoundShaderProgram() != _gameObject->getShader()->shaderProgram){
				shaderManager->updateAttribs(_gameObject->getShader()->name, _gameObject->getMeshRenderer()->mesh);
				_gameObject->getMeshRenderer()->mesh->setBoundShaderProgram(shaderManager->getCurrShader()->shaderProgram);
			}
			//Send Model View Projection to the shader
			glUniformMatrix4fv(shaderManager->getCurrShader()->mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
			//Bind GameObject's Texture if it exists
			if (_gameObject->getTexture() != nullptr){
				_gameObject->getTexture()->Bind(shaderManager->getCurrShader()->texSamplerLoc);
			}
			//Now render the GameObject!
			_gameObject->Draw();
			//Unbind GameObject Texture when done
			glBindTexture(GL_TEXTURE_2D, 0);
		}
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

	/*Drawing children*/
	std::vector<GameObject*> childs = _gameObject->getChildren();
	for (size_t i = 0; i < childs.size(); i++){
		RenderObject(childs[i]);
	}
}

void OpenGLRenderSystem::RenderDebugMesh(Mesh* _mesh){
	glBindVertexArray(_mesh->getVAO());
	std::vector<int> indiceCountData = _mesh->getIndiceCountData();
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

void OpenGLRenderSystem::EndRender(){

}
