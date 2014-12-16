#pragma once
#include <stdio.h>
#include "ConfigManager.h"
#include "vgl.h";
// Include GLFW
#include <GLFW\glfw3.h>

class Window {
private:
	GLFWwindow* window;
	const char* name;
	int width, height;
	ConfigManager* configManager;
	LogManager* logManager;
public:
	Window();
	~Window();
	GLFWwindow* getGLFWWindowInstance();
	int getWindowWidth();
	int getWindowHeight();
	void setWindowDimensions(int _width, int _height);
	void setKeyboardFunc(GLFWkeyfun _keyboardFunc);
	void setWindowSizeFunc(GLFWwindowsizefun _windowFunc);
	void windowInit();
	void closeWindow();
};

