#pragma once
#include "vgl.h";
#include "Camera.h"
#include "ShaderManager.h"
#include "GameObject.h"

class Renderer {
private:
	Camera* activeCamera;
	ShaderManager* shaderManager;
	Shader* currShader;
	glm::mat4 cam;
	glm::mat4 proj;
	Mesh* boxColliderMesh;
	Mesh* sphereColliderMesh;
	Shader* debugShader;
	void RenderDebugMesh(Mesh* _mesh);
public:
	Renderer();
	virtual ~Renderer();
	void Init();
	void setActiveCamera(Camera* _camera);
	void PreRender();
	void RenderObject(GameObject* _gameObject);
	void EndRender();
	bool isDebugOn;
};

