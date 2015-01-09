#pragma once
#include "Engine.h"

class DemoApp : public bobcat::Engine {
private:
	bobcat::Scene* scene;
	bobcat::GameObject* cubeObj;
	bobcat::GameObject* torusObj;
	bobcat::GameObject* circleObj;
	bobcat::GameObject* planeObj;
	bobcat::GameObject* cameraObj;

	glm::vec3 sphereTorque;
	glm::vec3 origCameraPos;
	glm::vec3 sphereOrigPos;

	bobcat::Ray* ray;

	bobcat::Material* mat;
	bobcat::Material* noTexMat;
	glm::vec3 lightSource;

	int mode;
	int renderMode;
	bool debugRenderOn;
public:
	DemoApp();
	DemoApp(int _engineCmd);
	virtual ~DemoApp();
	virtual void Init();
	virtual void OnKeyEvent();
	virtual void Update();
	virtual void InputUpdate();
	virtual void Draw();
	void Quit();
};

class TestDisplayPosition : public bobcat::Component {
public:
	TestDisplayPosition(){}
	virtual void Update(float _deltaTime){
		TestDisplay();
	}
	void TestDisplay(){
		printf("(%f, %f, %f)\n", gameObject->transform->position.x, gameObject->transform->position.y, gameObject->transform->position.z);
	}
};