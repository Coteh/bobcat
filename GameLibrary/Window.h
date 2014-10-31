#pragma once
#include <stdio.h>
#include "vgl.h";
// Include GLFW
#include <GLFW\glfw3.h>

class Window {
private:
	GLFWwindow* window;
	int width, height;
public:
	Window();
	~Window();
	GLFWwindow* getGLFWWindowInstance();
	int getWindowWidth();
	int getWindowHeight();
	void setWindowDimensions(int _width, int _height);
	void windowInit();
	void closeWindow();
};

