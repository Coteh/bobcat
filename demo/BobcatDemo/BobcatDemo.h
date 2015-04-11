#pragma once
#include "Engine.h"

class BobcatDemo : public bobcat::Engine {
private:
	bobcat::Scene* scene;
	bobcat::GameObject* cubeObj;
	bobcat::GameObject* torusObj;
	bobcat::GameObject* circleObj;
	bobcat::GameObject* planeObj;
	bobcat::GameObject* cameraObj;
	bobcat::GameObject* cameraChildObj;

	glm::vec3 sphereTorque;
	glm::vec3 origCameraPos;
	glm::vec3 sphereOrigPos;

	bobcat::Ray* ray;
	bool rayOnTopOfCube;

	bobcat::Material* mat;
	bobcat::Material* moonMat;
	bobcat::Material* noTexMat;
	std::vector<glm::vec3> cubeObjColor;
	glm::vec3 lightSource;

	int mode;
	int renderMode;
	bool debugRenderOn;

	float ballShatteringTime;
	int ballIndex;
public:
	BobcatDemo();
	BobcatDemo(int _engineCmd);
	virtual ~BobcatDemo();
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