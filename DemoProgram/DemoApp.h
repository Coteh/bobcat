#pragma once
#include "Engine.h"

class DemoApp : public Engine {
private:
	Scene* scene;
	GameObject* cubeObj;
	GameObject* squareObj;
public:
	DemoApp();
	~DemoApp();
	virtual void Init();
	virtual void Update();
	virtual void Draw();
};

