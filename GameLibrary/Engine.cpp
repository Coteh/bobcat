#include "Engine.h"


Engine::Engine() {
	window = new Window();
	renderer = new Renderer();
	meshManager = MeshManager::getInstance();
	sceneManager = SceneManager::getInstance();
	isGameRunning = true;
}

bool Engine::getIsGameRunning(){
	return isGameRunning;
}

bool Engine::getIsWindowRunning(){
	return !glfwWindowShouldClose(window->getGLFWWindowInstance());
}

void Engine::setScreenDimensions(int _width, int _height){
	window->setWindowDimensions(_width, _height);
}

void Engine::setGameRunning(bool _expression){
	isGameRunning = _expression;
}

void Engine::setKeyboardFunc(void* _function){
	window->setKeyboardFunc((GLFWkeyfun)_function);
}

void Engine::Init(){
	//inputManager = InputManager::getInstance();
	window->windowInit();
	renderer->Init();

	camera = new Camera();
	camera->setCameraScreenDimensions(window->getWindowWidth(), window->getWindowHeight());
	camera->setZoom(10.0f);
	renderer->setCamera(camera);
	camera->UpdateCamera(); //Initial camera update
}

void Engine::OnKeyEvent(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods){
	
}

void Engine::Update(){

}

void Engine::DrawBegin(){
	renderer->PreRender();
}

void Engine::Draw(){

}

void Engine::DrawEnd(){
	renderer->EndRender();
	glfwSwapBuffers(window->getGLFWWindowInstance());
	glfwPollEvents();
}

Engine::~Engine() {
	delete window;
	delete sceneManager;
	glfwTerminate();
	exit(EXIT_SUCCESS);
}