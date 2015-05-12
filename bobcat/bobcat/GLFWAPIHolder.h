#pragma once
#include "GLFWWindower.h"
#include "GLFWInputSystem.h"

namespace bobcat {

	/**
	* Static class holding GLFW API functions.
	*/
	class GLFWAPIHolder {
	private:
		static GLFWWindower* glfwWindower;
		static GLFWInputSystem* glfwInputSystem;
	public:
		/**
		* Register GLFW classes to receive callbacks.
		* @param _glfwWindower GLFWWindower instance to receive window-related callbacks.
		* @param _glfwInputSystem GLFWInputSystem instance to receive input-related callbacks.
		*/
		static void registerGLFWSystems(GLFWWindower* _glfwWindower, GLFWInputSystem* _glfwInputSystem);

		/**
		* GLFW Window resize callback with GLFWwindowsizefun signature.
		*/
		static void GLFWWindowSizeCallback(GLFWwindow* _window, int _width, int _height);

		/**
		* GLFW Keyboard callback with GLFWkeyfun signature.
		*/
		static void GLFWKeyFun(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);

		static void GLFWWindowFocusCallback(GLFWwindow* _window, int _focused);

		/**
		* GLFW error callback with GLFWerrorfun signature.
		*/
		static void GLFWErrorCallback(int _error, const char* _descrip);
	};

}