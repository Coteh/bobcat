#pragma once

#include "Clock.h"
#include "Window.h"
#include "LogManager.h"
//#include "InputManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "PLYModelReader.h"
#include "CollisionMath.h"
#include "Ray.h"

#define GAME_RUNNING true
#define GAME_END false

class Engine {
private:
	Window* window;

	bool isKeyPressed;
protected:
	LogManager* logManager;
	//InputManager* inputManager;
	Renderer* renderer;
	Camera* camera;
	SceneManager* sceneManager;
	ResourceManager* resourceManager;
	ShaderManager* shaderManager;

	GLFWwindow* currActiveWindowInstance;
	int lastKeyAction;

	float gameTime = 0.0f;
	float deltaTime = 0.016f;
	bool isGameRunning;
public:
	Engine();
	virtual ~Engine();
	bool getIsGameRunning();
	bool getIsWindowRunning();
	void setScreenDimensions(int _width, int _height);
	void setGameRunning(bool _expression);
	void setKeyboardFunc(void* _function);
	void setWindowSizeFunc(void* _function);
	virtual void Init();
	virtual void OnKeyEvent(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
	virtual void OnKeyHandle();
	virtual void OnWindowResize(int _width, int _height);
	virtual void Update();
	void DrawBegin();
	virtual void Draw();
	void DrawEnd();
};

