#pragma once
#include "vgl.h";
#include "Camera.h"
#include "ShaderManager.h"
#include "GameObject.h"
class Renderer {
private:
	Camera* camera;
	GLuint modelLoc, projectionLoc, cameraLoc, lightingLoc;
public:
	Renderer();
	virtual ~Renderer();
	void Init();
	void setCamera(Camera* _camera);
	void SwitchShader(GLuint _program);
	void UpdateLocations(GLuint _program);
	void PreRender();
	void RenderObject(GameObject* _gameObject);
	void EndRender();
};

