#include "Engine.h"


Engine::Engine() {
	window = new Window();
	renderer = new Renderer();
	meshManager = MeshManager::getInstance();
	sceneManager = SceneManager::getInstance();
	shaderManager = ShaderManager::getInstance();
	textureManager = TextureManager::getInstance();
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

void Engine::setWindowSizeFunc(void* _function){
	window->setWindowSizeFunc((GLFWwindowsizefun)_function);
}

void Engine::Init(){
	//inputManager = InputManager::getInstance();
	window->windowInit();
	currActiveWindowInstance = window->getGLFWWindowInstance();
	renderer->Init();

	camera = new Camera();
	camera->setCameraScreenDimensions(window->getWindowWidth(), window->getWindowHeight());
	camera->setZoom(10.0f);
	renderer->setCamera(camera);
	camera->UpdateCamera(); //Initial camera update
}

void Engine::OnKeyEvent(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods){
	currActiveWindowInstance = _window;
	isKeyPressed = (_action == GLFW_PRESS || _action == GLFW_REPEAT || (_action == GLFW_RELEASE && lastKeyAction == GLFW_PRESS) || (_action == GLFW_RELEASE && lastKeyAction == GLFW_REPEAT));
	lastKeyAction = _action;
}

void Engine::OnKeyHandle(){
	
}

void Engine::OnWindowResize(int _width, int _height){
	window->setWindowDimensions(_width, _height);
	glViewport(0,0,_width, _height);
	camera->setCameraScreenDimensions(_width, _height);
	camera->UpdateProjection();
}

void Engine::Update(){
	//if (isKeyPressed){
		OnKeyHandle();
	//}
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
	delete shaderManager;
	glfwTerminate();
	exit(EXIT_SUCCESS);
}