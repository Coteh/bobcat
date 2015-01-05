#pragma once
#include "GLFWWindower.h"
#include "GLFWInputSystem.h"

class GLFWAPIHolder {
private:
	static GLFWWindower* glfwWindower;
	static GLFWInputSystem* glfwInputSystem;
public:
	static void registerGLFWSystems(GLFWWindower* _glfwWindower, GLFWInputSystem* _glfwInputSystem);

	static void GLFWWindowSizeCallback(GLFWwindow* _window, int _width, int _height);

	static void GLFWKeyFun(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
};

