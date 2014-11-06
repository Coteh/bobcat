#pragma once

#include "Window.h"
//#include "InputManager.h"
#include "Renderer.h"
#include "MeshManager.h"
#include "SceneManager.h"
#include "PLYModelReader.h"
#include "CollisionMath.h"

#define GAME_RUNNING true
#define GAME_END false

class Engine {
private:
	Window* window;
	Camera* camera;

	bool isGameRunning;
protected:
	//InputManager* inputManager;
	Renderer* renderer;
	SceneManager* sceneManager;
	MeshManager* meshManager;
	IModelReader* modelReader;

	float gameTime = 0.016f;
public:
	Engine();
	~Engine();
	bool getIsGameRunning();
	bool getIsWindowRunning();
	void setScreenDimensions(int _width, int _height);
	void setGameRunning(bool _expression);
	void setKeyboardFunc(void* _function);
	virtual void Init();
	virtual void OnKeyEvent(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
	virtual void Update();
	void DrawBegin();
	virtual void Draw();
	void DrawEnd();
};

