#include "Engine.h"

Engine::Engine() {
	logManager = LogManager::getInstance();
	logManager->setDefaultLogFileName("EngineLog.txt");
	configManager = ConfigManager::getInstance();
	configManager->readConfigFile("engine.config");
	Clock::init();
	window = new GLFWWindower();
	renderer = new OpenGLRenderSystem();
	resourceManager = ResourceManager::getInstance();
	sceneManager = SceneManager::getInstance();
	shaderManager = ShaderManager::getInstance();
	isGameRunning = true;
}

Engine::Engine(int _engineCmd) : Engine(){
	if (_engineCmd){
		Init();
	}
}

bool Engine::getIsGameRunning(){
	return isGameRunning;
}

bool Engine::getIsWindowRunning(){
	return window->isRunning();
}

Camera* Engine::getMainCamera(){
	return mainCamera;
}

void Engine::setScreenDimensions(int _width, int _height){
	window->setWindowDimensions(_width, _height);
}

void Engine::setGameRunning(bool _expression){
	isGameRunning = _expression;
}

void Engine::setKeyboardFunc(void* _function){
	((GLFWWindower*)window)->setKeyboardFunc((GLFWkeyfun)_function);
}

void Engine::setWindowSizeFunc(void* _function){
	((GLFWWindower*)window)->setWindowSizeFunc((GLFWwindowsizefun)_function);
}

void Engine::setMainCamera(Camera* _camera){
	mainCamera = _camera;
	mainCamera->setCameraScreenDimensions(window->getWidth(), window->getHeight());
	renderer->setActiveCamera(mainCamera);
	mainCamera->UpdateProjection(); //Initial camera projection update
	mainCamera->UpdateCamera(); //Initial camera view update
}

void Engine::Init(){
	//inputManager = InputManager::getInstance();
	window->init();
	renderer->Init();

	resourceManager->addMesh(RESOUR_MODELNOTFOUND + std::string(".ply"), RESOUR_MODELNOTFOUND);
	resourceManager->loadTexture(RESOUR_TEXTURENOTFOUND + std::string(".png"), RESOUR_TEXTURENOTFOUND);
}

void Engine::OnKeyEvent(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods){
	isKeyPressed = (_action == GLFW_PRESS || _action == GLFW_REPEAT || (_action == GLFW_RELEASE && lastKeyAction == GLFW_PRESS) || (_action == GLFW_RELEASE && lastKeyAction == GLFW_REPEAT));
	lastKeyAction = _action;
}

void Engine::OnKeyHandle(){
	
}

void Engine::OnWindowResize(GLFWwindow* _window, int _width, int _height){
	window->setWindowDimensions(_width, _height);
	glViewport(0,0,_width, _height);
	mainCamera->setCameraScreenDimensions(_width, _height);
	mainCamera->UpdateProjection();
}

void Engine::Update(){
	float newGameTime = Clock::getCurrentTime();
	deltaTime = newGameTime - gameTime;
	gameTime = newGameTime;
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
	window->updateWindow();
}

void Engine::Run(){
	while (isGameRunning && window->isRunning()){
		Update();
		DrawBegin();
		Draw();
		DrawEnd();
	}
}

Engine::~Engine() {
	delete window;
	delete logManager;
	delete configManager;
	delete sceneManager;
	delete resourceManager;
	delete shaderManager;
	exit(EXIT_SUCCESS);
}