#include "GLFWWindower.h"
#include "GLFWAPIHolder.h"
#include "OpenGLHelpers.h"

using namespace bobcat;

GLFWWindower::GLFWWindower(){
	logManager = LogManager::getInstance();
	//Set default window settings
	name = "Engine Window (GLFW)";
	width = 640;
	height = 640;
}

GLFWWindower::~GLFWWindower(){
	glfwDestroyWindow(window);
	glfwTerminate();
}

int GLFWWindower::getWidth(){
	return width;
}

int GLFWWindower::getHeight(){
	return height;
}

const char* GLFWWindower::getName(){
	return name;
}

bool GLFWWindower::isVisible(){
	return glfwGetWindowAttrib(window, GLFW_VISIBLE);
}

bool GLFWWindower::isRunning(){
	return !glfwWindowShouldClose(window);
}

bool GLFWWindower::isFocused() {
	return isWindowFocused;
}

void GLFWWindower::setWindowDimensions(int _width, int _height){
	glfwSetWindowSize(window, _width, _height);
	if (isOpenGLLoaded){
		glViewport(0, 0, _width, _height);
	}
	width = _width;
	height = _height;
}

void GLFWWindower::setName(const char* _name){
	glfwSetWindowTitle(window, _name);
	name = _name;
}

void GLFWWindower::setWindowStyle(WindowStyle _windowStyle){
	//No implementation exists yet.
	//So no fullscreen GLFW yet.
}

void GLFWWindower::showWindow(int _expression){
	if (!_expression){
		glfwHideWindow(window);
	} else{
		glfwShowWindow(window);
	}
}

void GLFWWindower::init(){
	//Initalize GLFW
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

	//Set up OpenGL version
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Set GLFW error callback
	glfwSetErrorCallback(GLFWAPIHolder::GLFWErrorCallback);

	//Create the GLFW window
	window = glfwCreateWindow(width, height, name, NULL, NULL);
	//Check if window creation was unsuccessful (window is null)
	if (!window) {
		glfwTerminate();
		logManager->log(LogLevel::LOG_ERROR, "Could not initalize GLFW window!");
		exit(EXIT_FAILURE);
	} else {
		logManager->log(LogLevel::LOG_INFO, "GLFW window initalized successfully!");
	}

	//Make the window context current
	glfwMakeContextCurrent(window);

	//Loading OpenGL functions
	if (!OpenGLHelpers::loadOpenGL()){
		logManager->log(LogLevel::LOG_ERROR, "OpenGL functions could not load! Exiting...");
		exit(0);
	} else {
		isOpenGLLoaded = true;
	}

	//Currently not in use.
	//glfwGetFramebufferSize(window, &width, &height);

	//Initalizing OpenGL Viewport
	glViewport(0, 0, width, height);

	//Print Info of OpenGL and graphics card drivers (for testing)
	OpenGLHelpers::printVersionInfo();

	//Enable the GL Depth Test
	glEnable(GL_DEPTH_TEST);
	//Set GL Depth Function
	glDepthFunc(GL_LESS);

	//Set GLFW Window Changed Callback
	glfwSetWindowSizeCallback(window, GLFWAPIHolder::GLFWWindowSizeCallback);

	//Set GLFW Keyboard Callback
	glfwSetKeyCallback(window, GLFWAPIHolder::GLFWKeyFun);

	//Set GLFW Window Focus Callback
	glfwSetWindowFocusCallback(window, GLFWAPIHolder::GLFWWindowFocusCallback);
	//GLFW focus callback doesn't seem to callback on initial window focus, so this is being set to true for now
	isWindowFocused = true;
}

void GLFWWindower::updateWindow(){
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void GLFWWindower::closeWindow(){
	glfwSetWindowShouldClose(window, GL_TRUE);
}

int GLFWWindower::getGLFWKeyState(int _key){
	return glfwGetKey(window, _key);
}

void GLFWWindower::notifyObservers() {
	for (size_t i = 0; i < observerFuncVec.size(); i++){
		((void(*)(int, int))observerFuncVec[i])(width, height);
	}
}

void GLFWWindower::OnWindowChanged(GLFWwindow* _window, int _width, int _height) {
	setWindowDimensions(_width, _height);
	notifyObservers();
}