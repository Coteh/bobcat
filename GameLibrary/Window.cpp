#include "Window.h"

void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void printVersionInfo() {
	printf("============================================================\n");
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("OpenGL Shading Language Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	printf("============================================================\n\n");
}

Window::Window() {
	configManager = ConfigManager::getInstance();
	logManager = LogManager::getInstance();
	//Set default window settings
	name = "Engine Window";
	width = 640;
	height = 640;
}

Window::~Window() {
	glfwDestroyWindow(window);
}

GLFWwindow* Window::getGLFWWindowInstance(){
	return window;
}

int Window::getWindowWidth(){
	return width;
}

int Window::getWindowHeight(){
	return height;
}

void Window::setWindowDimensions(int _width, int _height){
	width = _width;
	height = _height;
}

void Window::setKeyboardFunc(GLFWkeyfun _keyboardFunc){
	glfwSetKeyCallback(window, _keyboardFunc);
}

void Window::setWindowSizeFunc(GLFWwindowsizefun _windowFunc){
	glfwSetWindowSizeCallback(window, _windowFunc);
}

void Window::windowInit(){
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
	glfwSetErrorCallback(error_callback);

	//Get window settings from Config Manager
	configManager->getWindowSettings(name, width, height);

	//Create the GLFW window
	window = glfwCreateWindow(width, height, name, NULL, NULL);
	//Check if window creation was unsuccessful (window is null)
	if (!window) {
		glfwTerminate();
		logManager->writeLog(LogLevel::LOG_ERROR, "Could not initalize window!");
		exit(EXIT_FAILURE);
	}

	//Make the window context current
	glfwMakeContextCurrent(window);

	//Currently not in use.
	//glfwGetFramebufferSize(window, &width, &height);

	/*Initalizing OpenGL Viewport*/
	glViewport(0, 0, width, height);

	//Turn on GLEW Experimental
	glewExperimental = GL_TRUE;
	glewInit();

	//Print Info of OpenGL and graphics card drivers (for testing)
	printVersionInfo();

	//Enable the GL Depth Test
	glEnable(GL_DEPTH_TEST);
	//Set GL Depth Function
	glDepthFunc(GL_LESS);
}

void Window::closeWindow(){
	glfwSetWindowShouldClose(window, GL_TRUE);
}