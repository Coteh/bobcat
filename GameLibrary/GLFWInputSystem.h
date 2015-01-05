#pragma once
#include "AbstractInputSystem.h"
#include "GLFWWindower.h"
#include <vector>

class GLFWInputSystem : public AbstractInputSystem {
private:
	GLFWWindower* m_glfwWindower;
	bool m_isKeyPressed;
	int m_lastKeyAction;

	std::vector<void*> listenerFuncVec;
protected:
	virtual int translateKeyCodeInput(int _keyCode);
	virtual int translateInputStateOutput(int _inputState);
public:
	GLFWInputSystem(GLFWWindower* _glfwWindower);

	virtual int getInputState(int _keyCode);

	void setGLFWWindower(GLFWWindower* _glfwWindower);
	virtual void setKeyboardCallback(void* _keyboardFunc);

	virtual bool isKeyPressed();

	virtual void registerListener(void* _listenerFunc);
	virtual void notifyListeners();

	void GLFWKeyboardEvent(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);

	static void GLFWKeyFun(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods) {
		if (currentInputSystem != nullptr){
			((GLFWInputSystem*)currentInputSystem)->GLFWKeyboardEvent(_window, _key, _scancode, _action, _mods);
		}
	}

	virtual ~GLFWInputSystem();
};

