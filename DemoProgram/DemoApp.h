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
	Material* mat;
	Material* noTexMat;
	glm::vec3 lightSource;
	int mode;
	int renderMode;
	bool debugRenderOn;
public:
	DemoApp();
	DemoApp(int _engineCmd);
	virtual ~DemoApp();
	virtual void Init();
	virtual void OnKeyEvent(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
	virtual void OnKeyHandle();
	virtual void Update();
	virtual void Draw();
};

class TestComponent : public Component {
public:
	int testNum;
	TestComponent(){ name = "TestComponent"; testNum = 10; }
};