#include "GLFWAPIHolder.h"

GLFWWindower* GLFWAPIHolder::glfwWindower;
GLFWInputSystem* GLFWAPIHolder::glfwInputSystem;

void GLFWAPIHolder::registerGLFWSystems(GLFWWindower* _glfwWindower, GLFWInputSystem* _glfwInputSystem) {
	glfwWindower = _glfwWindower;
	glfwInputSystem = _glfwInputSystem;
}

void GLFWAPIHolder::GLFWWindowSizeCallback(GLFWwindow* _window, int _width, int _height) {
	if (glfwWindower != nullptr) {
		glfwWindower->OnWindowChanged(_window, _width, _height);
	}
}

void GLFWAPIHolder::GLFWKeyFun(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods) {
	if (glfwInputSystem != nullptr){
		glfwInputSystem->GLFWKeyboardEvent(_window, _key, _scancode, _action, _mods);
	}
}

void GLFWAPIHolder::GLFWErrorCallback(int _error, const char* _descrip) {
	fputs(_descrip, stderr);
}