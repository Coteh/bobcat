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
public:
	Renderer();
	virtual ~Renderer();
	void Init();
	void setCamera(Camera* _camera);
	void PreRender();
	void RenderObject(GameObject* _gameObject);
	void EndRender();
};

