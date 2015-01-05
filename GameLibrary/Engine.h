#pragma once

#include "Clock.h"
#include "AbstractWindower.h"
#include "LogManager.h"
#include "ConfigManager.h"
#include "AbstractInputSystem.h"
#include "AbstractRenderSystem.h"
#include "ShaderManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "PLYModelReader.h"
#include "CollisionMath.h"
#include "Ray.h"
#include "GameObjectCreator.h"

#define GAME_RUNNING true
#define GAME_END false

#define ENGINE_INIT 1
#define ENGINE_CONSTRUCT 0

class Engine {
private:
	Camera* m_mainCamera;
protected:
	AbstractWindower* window;
	LogManager* logManager;
	ConfigManager* configManager;
	AbstractInputSystem* inputSystem;
	AbstractRenderSystem* renderer;
	SceneManager* sceneManager;
	ResourceManager* resourceManager;
	ShaderManager* shaderManager;

	Camera* getMainCamera();
	void setMainCamera(Camera* _camera);
	__declspec(property(get = getMainCamera, put = setMainCamera)) Camera* mainCamera;

	float gameTime = 0.0f;
	float deltaTime = 0.016f;
	bool isGameRunning;
public:
	Engine();
	Engine(int _engineCmd);
	virtual ~Engine();
	bool getIsGameRunning();
	bool getIsWindowRunning();
	void setScreenDimensions(int _width, int _height);
	void setGameRunning(bool _expression);
	void setKeyboardCallback(void* _keyboardFunc);
	void setWindowChangedCallback(void* _windowFunc);
	virtual void Init();
	virtual void OnKeyEvent();
	virtual void OnWindowResize(int _width, int _height);
	virtual void Update();
	virtual void InputUpdate();
	void DrawBegin();
	virtual void Draw();
	void DrawEnd();
	void Run();

	AbstractInputSystem* getInputSystem();
	AbstractWindower* getWindower();
};

