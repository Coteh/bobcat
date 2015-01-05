#pragma once
#include "AbstractWindower.h"
#include "ConfigManager.h"
// Include OpenGL
#include "vgl.h";
// Include GLFW
#include <GLFW\glfw3.h>

class GLFWWindower : public AbstractWindower {
	friend class GLFWInputSystem;
private:
	GLFWwindow* window;
	const char* name;
	int width, height;
	ConfigManager* configManager;
	LogManager* logManager;

	std::vector<void*> listenerFuncVec;

	void setKeyboardCallback(GLFWkeyfun _keyboardFunc);

	static GLFWWindower* currentlyActiveGLFWWindow;
public:
	GLFWWindower();
	virtual ~GLFWWindower();
	virtual int getWidth();
	virtual int getHeight();
	virtual const char* getName();
	virtual bool isVisible();
	virtual bool isRunning();
	virtual void setWindowDimensions(int _width, int _height);
	virtual void setWindowChangedCallback(void* _windowFunc);
	virtual void setName(const char* _name);
	virtual void showWindow(int _expression);
	virtual void init();
	virtual void updateWindow();
	virtual void closeWindow();

	int getGLFWKeyState(int _key);

	void OnWindowChanged(GLFWwindow* _window, int _width, int _height);

	virtual void registerListener(void* _listenerFunc);
	virtual void notifyListeners();

	static GLFWWindower* getCurrentlyActiveGLFWWindow();
	static void setCurrentlyActiveGLFWWindow(GLFWWindower* _glfwWindower);

	static void GLFWWindowSizeCallback(GLFWwindow* _window, int _width, int _height) {
		if (currentlyActiveGLFWWindow != nullptr) {
			currentlyActiveGLFWWindow->OnWindowChanged(_window, _width, _height);
		}
	}
};

