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
	configHolder = new ConfigHolder();
	configHolder->readConfigFile(CONFIG_FILE);
	if (configHolder->hasSetting("log-settings")){
		LogSettings logSettings;
		logSettings.writePriority = configHolder->getInt("log-settings.write-priority-level");
		logSettings.printPriority = configHolder->getInt("log-settings.print-priority-level");
		logManager->setLogSettings(logSettings);
	}
	//Setting up clock
	Clock::init();
	deltaTime = 0.0f;
	gameTime = 0.0f;
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
	if (configHolder->hasSetting("window")){
		//Get window settings from Config Manager
		window->setName(configHolder->getString("window.title"));
		window->setWindowDimensions(configHolder->getInt("window.width"), configHolder->getInt("window.height"));
		//Messy territory right around here lol
		WindowStyle windowStyle = WindowStyle::DEFAULT;
		if (strcmp(configHolder->getString("window.style").c_str(), "fullscreen") == 0) {
			windowStyle = WindowStyle::FULL_SCREEN;
		}
		window->setWindowStyle(windowStyle);
	}
	//Setting up content paths (This must be done before the next step!)
	resourceManager = ResourceManager::getInstance();
	if (configHolder->hasSetting("content-paths")){
		resourceManager->provideAssetPaths(configHolder->getString("content-paths.models"), configHolder->getString("content-paths.textures"));
		ShaderLoader::ProvideShaderLoadPath(configHolder->getString("content-paths.shaders"));
	}
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
	//Initialize window
	window->init();
	//Initialize renderer
	renderer->Init();

	/*Load in built-in resources*/
	//Load models
	resourceManager->addMesh(RESOUR_MODELNOTFOUND + std::string(".ply"), RESOUR_MODELNOTFOUND);
	//Load textures
	resourceManager->loadTexture(RESOUR_TEXTURENOTFOUND + std::string(".png"), RESOUR_TEXTURENOTFOUND);
	//Load basic shaders
	ShaderLoadInfo colorShader[] = {
		{ GL_VERTEX_SHADER, "colormodel-vert.glsl" },
		{ GL_FRAGMENT_SHADER, "colormodel-frag.glsl" },
		{ GL_NONE, NULL }
	};
	ShaderLoadInfo uniformColorShader[] = {
		{ GL_VERTEX_SHADER, "basic-vert.glsl" },
		{ GL_FRAGMENT_SHADER, "uniformcolor-frag.glsl" },
		{ GL_NONE, NULL }
	};
	shaderManager->addShader(ShaderLoader::LoadShaders(colorShader), "VertexColorModel");
	shaderManager->addShader(ShaderLoader::LoadShaders(uniformColorShader), "UniformColorModel");
	//Load shaders needed for components
	ShaderLoadInfo particleShader[] = {
		{ GL_VERTEX_SHADER, "particle-vert.glsl" },
		{ GL_FRAGMENT_SHADER, "colormodel-frag.glsl" },
		{ GL_NONE, NULL }
	};
	shaderManager->addShader(ShaderLoader::LoadShaders(particleShader), "ParticleShader");
}

void Engine::InputUpdate() {

}

void Engine::OnKeyEvent() {}

void Engine::OnWindowResize(int _width, int _height){
	m_mainCamera->setCameraScreenDimensions(_width, _height);
	m_mainCamera->UpdateProjection();
}

void Engine::Update(){
	if (inputSystem != nullptr && window->isFocused()){
		InputUpdate();
	}
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
		float newGameTime = Clock::getCurrentTime();
		deltaTime = newGameTime - gameTime;
		gameTime = newGameTime;
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
	delete sceneManager;
	delete resourceManager;
	delete shaderManager;
	exit(EXIT_SUCCESS);
}