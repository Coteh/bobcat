#include "Engine.h"
#include "GLFWWindower.h"
#include "SFMLWindower.h"
#include "GLFWInputSystem.h"
#include "SFMLInputSystem.h"
#include "OpenGLRenderSystem.h"
#include "GLFWAPIHolder.h"

using namespace bobcat;

Engine::Engine() {
	//Setting up Engine I/O
	logManager = LogManager::getInstance();
	logManager->setLogfile("EngineLog.txt");
	configManager = ConfigManager::getInstance();
	configManager->readConfigFile(CONFIG_FILE);
	//Setting up clock
	Clock::init();
	//Setting up windowing
#ifdef WINDOWING_GLFW
	window = new GLFWWindower();
	inputSystem = new GLFWInputSystem((GLFWWindower*)window);
	GLFWAPIHolder::registerGLFWSystems((GLFWWindower*)window, (GLFWInputSystem*)inputSystem);
#endif
#ifdef WINDOWING_SFML
	window = new SFMLWindower();
	inputSystem = new SFMLInputSystem((SFMLWindower*)window);
#endif
	//Setting up content paths (This must be done before the next step!)
	resourceManager = ResourceManager::getInstance();
	AssetPaths assetPaths;
	configManager->getAssetLoadPaths(&assetPaths);
	resourceManager->provideAssetPaths(assetPaths.modelPath, assetPaths.texPath);
	ShaderLoader::ProvideShaderLoadPath(assetPaths.shadersPath);
	//Setting up everything else
	renderer = new OpenGLRenderSystem();
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
	return m_mainCamera;
}

void Engine::setScreenDimensions(int _width, int _height){
	window->setWindowDimensions(_width, _height);
}

void Engine::setGameRunning(bool _expression){
	isGameRunning = _expression;
}

void Engine::setMainCamera(Camera* _camera){
	m_mainCamera = _camera;
	m_mainCamera->setCameraScreenDimensions(window->getWidth(), window->getHeight());
	renderer->setActiveCamera(m_mainCamera);
	m_mainCamera->UpdateProjection(); //Initial camera projection update
	m_mainCamera->UpdateCamera(); //Initial camera view update
}

void Engine::Init(){
	//inputManager = InputManager::getInstance();
	window->init();
	renderer->Init();

	resourceManager->addMesh(RESOUR_MODELNOTFOUND + std::string(".ply"), RESOUR_MODELNOTFOUND);
	resourceManager->loadTexture(RESOUR_TEXTURENOTFOUND + std::string(".png"), RESOUR_TEXTURENOTFOUND);
}

void Engine::InputUpdate() {

}

void Engine::OnKeyEvent() {}

void Engine::OnWindowResize(int _width, int _height){
	m_mainCamera->setCameraScreenDimensions(_width, _height);
	m_mainCamera->UpdateProjection();
}

void Engine::Update(){
	float newGameTime = Clock::getCurrentTime();
	deltaTime = newGameTime - gameTime;
	gameTime = newGameTime;
	InputUpdate();
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

AbstractWindower* Engine::getWindower() {
	return window;
}

AbstractInputSystem* Engine::getInputSystem() {
	return inputSystem;
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