#pragma once
#include "AbstractWindower.h"
#include "Notifier.h"
#include "ConfigManager.h"
// Include OpenGL
#include "vgl.h";
// Include GLFW
#include <GLFW\glfw3.h>

/**
* The GLFW implementation of AbstractWindower.
* It is used to interface directly with the GLFW windowing system.
*/
class GLFWWindower : public AbstractWindower, public Notifier {
	friend class GLFWInputSystem;
private:
	GLFWwindow* window;
	const char* name;
	int width, height;
	ConfigManager* configManager;
	LogManager* logManager;
protected:
	/**
	* Get GLFW-specific key state of supplied key.
	* @note This is used to supply key state information to GLFWInputSystem.
	*/
	int getGLFWKeyState(int _key);

	virtual void notifyObservers();
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

	/**
	* Receives the Window Changed callback from the GLFW API.
	*/
	void OnWindowChanged(GLFWwindow* _window, int _width, int _height);
};

