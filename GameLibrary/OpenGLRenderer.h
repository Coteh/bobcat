#pragma once
#include "AbstractRenderer.h"
#include "vgl.h";
#include "Camera.h"
#include "ShaderManager.h"
#include "GameObject.h"

class OpenGLRenderer : public AbstractRenderer {
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
	OpenGLRenderer();
	virtual ~OpenGLRenderer();
	virtual void setActiveCamera(Camera* _camera);
	virtual void setDebugRender(bool _expression);
	virtual void Init();
	virtual void PreRender();
	virtual void RenderObject(GameObject* _gameObject);
	virtual void EndRender();
};

