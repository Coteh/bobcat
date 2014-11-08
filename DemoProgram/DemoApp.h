#pragma once
#include "Engine.h"

class DemoApp : public Engine {
private:
	Scene* scene;
	GameObject* cubeObj;
	GameObject* torusObj;
	GameObject* circleObj;
public:
	DemoApp();
	~DemoApp();
	virtual void Init();
	virtual void OnKeyEvent(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
	virtual void Update();
	virtual void Draw();
};

