#pragma once
#include "vgl.h";
#include "Camera.h"
#include "ShaderManager.h"
#include "GameObject.h"

class Renderer {
private:
	Camera* camera;
	ShaderManager* shaderManager;
	Shader* currShader;
	glm::mat4 cam;
	glm::mat4 proj;
	Mesh* boxColliderMesh;
	Mesh* sphereColliderMesh;
	void RenderDebugMesh(Mesh* _mesh);
public:
	Renderer();
	virtual ~Renderer();
	void Init();
	void setCamera(Camera* _camera);
	void PreRender();
	void RenderObject(GameObject* _gameObject);
	void EndRender();
	bool isDebugOn;
};

