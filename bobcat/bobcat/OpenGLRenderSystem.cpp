#include "OpenGLRenderSystem.h"
#include "ResourceManager.h"
#include "ShaderLoader.h"
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

using namespace bobcat;

OpenGLRenderSystem::OpenGLRenderSystem() {

}

OpenGLRenderSystem::~OpenGLRenderSystem() {
}

void OpenGLRenderSystem::Init(){
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
	debugShader = new Shader(ShaderLoader::LoadShaders(debugShaderInfo), "DebugShader");
	resourceManager->addShader(debugShader, debugShader->name);
}

void OpenGLRenderSystem::setActiveCamera(Camera* _camera){
	activeCamera = _camera;
}

void OpenGLRenderSystem::setDebugRender(bool _expression){
	isDebugOn = _expression;
}

void OpenGLRenderSystem::UseShader(Shader* _shader){
	_shader->disableShaderAttribs();
	glUseProgram(_shader->shaderProgram);
	currShader = _shader;
}

void OpenGLRenderSystem::PreRender(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderSystem::RenderObject(GameObject* _gameObject){
	glm::mat4 modelMat = _gameObject->getModelMat();

	if (_gameObject->renderer != nullptr){ //don't draw if mesh renderer is null
		Material* mat = _gameObject->renderer->material; //get a reference to the material
		if (mat != nullptr && mat->shader != nullptr){
			//Make sure OpenGL is always using the shader program that the GameObject is using
			if (!(currShader != nullptr && currShader->shaderProgram == mat->shader->shaderProgram)){
				UseShader(mat->shader);
			}
			Mesh* mesh = _gameObject->renderer->meshFilter->mesh; //get a reference to the mesh
			if (mesh == nullptr) return; //don't draw if mesh is null
			//Update Mesh attributes if the GameObject's shader is different than the one the mesh has at the moment
			if (!_gameObject->renderer->CheckShaderMatchup()){
				UpdateShaderAttribs(mat->shader, mesh);
				mesh->setBoundShaderProgram(currShader->shaderProgram);
			}
			//Get Uniform locations from the shader
			modelLoc = currShader->getShaderUniform("Model");
			viewLoc = currShader->getShaderUniform("View");
			projectionLoc = currShader->getShaderUniform("Projection");
			normalLoc = currShader->getShaderUniform("NormalMatrix");
			//Get view matrix from active camera
			glm::mat4 viewMat = activeCamera->getView();
			//Calculating normal matrix
			glm::mat4 normMat = glm::transpose(glm::inverse(viewMat * modelMat));
			//Send Model View Projection to the shader
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(activeCamera->getProjection()));
			glUniformMatrix3fv(normalLoc, 1, GL_FALSE, glm::value_ptr(normMat));
			//Render the GameObject
			_gameObject->Draw();
		}

	}

	/*Drawing Debug stuff*/
	if (isDebugOn){
		Collider* col = _gameObject->collider;
		if (col != nullptr){
			Mesh* colMesh;
			if (col->colliderType == ColliderType::SPHERE){
				colMesh = sphereColliderMesh;
			} else{
				colMesh = boxColliderMesh;
			}
			UseShader(debugShader);
			if (colMesh->getBoundShaderProgram() != debugShader->shaderProgram){
				UpdateShaderAttribs(debugShader, colMesh);
				colMesh->setBoundShaderProgram(debugShader->shaderProgram);
			}
			float colScale = col->getScale();
			glm::vec3 dimensions = col->getDimensions();
			//Let's just assume the collider position is always with the GameObject's position... hehehe :P
			//so just use the GameObject's MVP and not make a new matrix with its translation
			glm::mat4 debugMat = glm::scale(modelMat, glm::vec3(colScale * dimensions.x, colScale * dimensions.y, colScale * dimensions.z));
			glUniformMatrix4fv(debugShader->getShaderUniform("Model"), 1, GL_FALSE, glm::value_ptr(debugMat));
			RenderDebugMesh(colMesh);
		}
	}

	/*Drawing children*/
	std::vector<GameObject*> childs = _gameObject->getChildren();
	for (size_t i = 0; i < childs.size(); i++){
		RenderObject(childs[i]);
	}
}

void OpenGLRenderSystem::UpdateShaderAttribs(Shader* _shader, Mesh* _mesh){
	glBindVertexArray(_mesh->getVAO());
	glBindBuffer(GL_ARRAY_BUFFER, _mesh->getVBO());

	GLuint numParts = 11;
	size_t offset = 0;

	/*Specify that our coordinate data is going into attribute index 0 (vPosition), and contains
	three floats per vertex*/
	glVertexAttribPointer(_shader->posAttrib, 3, GL_FLOAT,
		GL_FALSE, numParts * sizeof(GLfloat), BUFFER_OFFSET(offset));
	/*Specify that our normal data is going into attribute index 1 (vNormals), and contains
	three floats per vertex*/
	offset += (3 * sizeof(GLfloat));
	glVertexAttribPointer(_shader->normAttrib, 3, GL_FLOAT,
		GL_FALSE, numParts * sizeof(GLfloat), BUFFER_OFFSET(offset));
	/*Specify that our uv data is going into attribute index 2 (vTexture), and contains
	two floats per vertex*/
	offset += (3 * sizeof(GLfloat));
	glVertexAttribPointer(_shader->texAttrib, 2, GL_FLOAT,
		GL_FALSE, numParts * sizeof(GLfloat), BUFFER_OFFSET(offset));
	/*Specify that our color data is going into attribute index 3 (vColor), and contains
	three floats per vertex*/
	offset += (2 * sizeof(GLfloat));
	glVertexAttribPointer(_shader->colAttrib, 3, GL_FLOAT,
		GL_FALSE, numParts * sizeof(GLfloat), BUFFER_OFFSET(offset));

	_shader->enableShaderAttribs();
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
