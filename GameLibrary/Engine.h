#pragma once

#include "Clock.h"
#include "GLFWWindower.h"
#include "LogManager.h"
#include "ConfigManager.h"
//#include "InputManager.h"
#include "OpenGLRenderSystem.h"
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
	Camera* mainCamera;
	bool isKeyPressed;
protected:
	AbstractWindower* window;
	LogManager* logManager;
	ConfigManager* configManager;
	//InputManager* inputManager;
	AbstractRenderSystem* renderer;
	SceneManager* sceneManager;
	ResourceManager* resourceManager;
	ShaderManager* shaderManager;

	Camera* getMainCamera();
	void setMainCamera(Camera* _camera);
	__declspec(property(get = getMainCamera, put = setMainCamera)) Camera* MainCamera;

	int lastKeyAction;

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
	void setKeyboardFunc(void* _function);
	void setWindowSizeFunc(void* _function);
	virtual void Init();
	virtual void OnKeyEvent(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
	virtual void OnKeyHandle();
	virtual void OnWindowResize(GLFWwindow* _window, int _width, int _height);
	virtual void Update();
	void DrawBegin();
	virtual void Draw();
	void DrawEnd();
	void Run();
};

