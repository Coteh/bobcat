#pragma once
#include "Engine.h"

class SquashApp : public Engine {
private:
	Scene* scene;
	GameObject* playerOne;
	GameObject* playerTwo;
	GameObject* ballObj;
	glm::vec3 ballVelChange;
	int ballHitter, score1, score2;
	const float ballSpeed = 0.1f;
	float ballSpeedMultiplier = 1.0f;
public:
	SquashApp();
	~SquashApp();
	virtual void Init();
	virtual void OnKeyEvent(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
	virtual void OnKeyHandle();
	virtual void Update();
	virtual void Draw();
};

