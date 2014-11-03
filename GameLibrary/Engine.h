#pragma once

#include "Window.h"
#include "Renderer.h"
#include "MeshManager.h"
#include "SceneManager.h"
#include "PLYModelReader.h"

#define GAME_RUNNING true
#define GAME_END false

class Engine {
private:
	Window* window;
	Camera* camera;

	bool isGameRunning;
protected:
	Renderer* renderer;
	SceneManager* sceneManager;
	MeshManager* meshManager;
	IModelReader* modelReader;

	float gameTime = 0.1f;
public:
	Engine();
	~Engine();
	bool getGameRunning();
	bool getWindowRunning();
	void setScreenDimensions(int _width, int _height);
	void setGameRunning(bool _expression);
	virtual void Init();
	virtual void Update();
	void DrawBegin();
	virtual void Draw();
	void DrawEnd();
};

