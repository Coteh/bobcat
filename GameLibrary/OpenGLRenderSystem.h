#pragma once
#include "AbstractRenderSystem.h"
#include "vgl.h";
#include "Camera.h"
#include "ShaderManager.h"
#include "GameObject.h"

class OpenGLRenderSystem : public AbstractRenderSystem {
private:
	Camera* activeCamera;
	ShaderManager* shaderManager;
	Shader* currShader;
	glm::mat4 cam;
	glm::mat4 proj;
	Mesh* boxColliderMesh;
	Mesh* sphereColliderMesh;
	Shader* debugShader;
	bool isDebugOn;
	void RenderDebugMesh(Mesh* _mesh);
public:
	OpenGLRenderSystem();
	virtual ~OpenGLRenderSystem();
	virtual void setActiveCamera(Camera* _camera);
	virtual void setDebugRender(bool _expression);
	virtual void Init();
	virtual void PreRender();
	virtual void RenderObject(GameObject* _gameObject);
	virtual void EndRender();
};

