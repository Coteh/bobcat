#include "Engine.h"


Engine::Engine() {
	window = new Window();
	renderer = new Renderer();
	meshManager = MeshManager::getInstance();
	sceneManager = SceneManager::getInstance();
	isGameRunning = true;
}

bool Engine::getGameRunning(){
	return isGameRunning;
}

bool Engine::getWindowRunning(){
	return !glfwWindowShouldClose(window->getGLFWWindowInstance());
}

void Engine::setScreenDimensions(int _width, int _height){
	window->setWindowDimensions(_width, _height);
}

void Engine::setGameRunning(bool _expression){
	isGameRunning = _expression;
}

void Engine::Init(){
	window->windowInit();
	renderer->Init();

	camera = new Camera();
	camera->setCameraScreenDimensions(window->getWindowWidth(), window->getWindowHeight());
	camera->setZoom(10.0f);
	renderer->setCamera(camera);
	camera->UpdateCamera(); //Initial camera update
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
	glfwTerminate();
	exit(EXIT_SUCCESS);
}