#pragma once
#include "AbstractWindower.h"
#include "ConfigManager.h"
// Include OpenGL
#include "vgl.h";
// Include GLFW
#include <GLFW\glfw3.h>

class GLFWWindower : public AbstractWindower {
private:
	GLFWwindow* window;
	const char* name;
	int width, height;
	ConfigManager* configManager;
	LogManager* logManager;
public:
	GLFWWindower();
	virtual ~GLFWWindower();
	virtual int getWidth();
	virtual int getHeight();
	virtual const char* getName();
	virtual bool isVisible();
	virtual bool isRunning();
	virtual void setWindowDimensions(int _width, int _height);
	virtual void setName(const char* _name);
	virtual void showWindow(int _expression);
	virtual void init();
	virtual void updateWindow();
	virtual void closeWindow();

	void setKeyboardFunc(GLFWkeyfun _keyboardFunc);
	void setWindowSizeFunc(GLFWwindowsizefun _windowFunc);
	int getGLFWKeyState(int _key);
};

