#pragma once
#include "Engine.h"

class DemoApp : public Engine {
private:
	Scene* scene;
	GameObject* cubeObj;
	GameObject* torusObj;
	GameObject* circleObj;
	GameObject* planeObj;
	glm::vec3 sphereTorque;
	glm::vec3 origCameraPos;
	glm::vec3 sphereOrigPos;
	Ray* ray;
	glm::vec3 lightSource;
	int mode;
	int renderMode;
public:
	DemoApp();
	virtual ~DemoApp();
	virtual void Init();
	virtual void OnKeyEvent(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
	virtual void OnKeyHandle();
	virtual void Update();
	virtual void Draw();
};

