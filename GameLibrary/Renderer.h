#pragma once
#include "vgl.h";
#include "Camera.h"
#include "ShaderManager.h"
#include "GameObject.h"
class Renderer {
private:
	Camera* camera;
	GLuint program;
	GLuint modelLoc, projectionLoc, cameraLoc, lightingLoc;
public:
	Renderer();
	virtual ~Renderer();
	void Init();
	void setCamera(Camera* _camera);
	void PreRender();
	void RenderObject(GameObject* _gameObject);
	void EndRender();
};

