#pragma once
#include "AbstractInputSystem.h"
#include "Notifier.h"
#include "GLFWWindower.h"
#include <vector>

class GLFWInputSystem : public AbstractInputSystem, public Notifier {
private:
	GLFWWindower* m_glfwWindower;
	bool m_isKeyPressed;
	int m_lastKeyAction;
protected:
	virtual int translateKeyCodeInput(int _keyCode);
	virtual int translateInputStateOutput(int _inputState);
public:
	GLFWInputSystem(GLFWWindower* _glfwWindower);

	virtual int getInputState(int _keyCode);

	void setGLFWWindower(GLFWWindower* _glfwWindower);

	virtual bool isKeyPressed();

	void GLFWKeyboardEvent(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);

	virtual ~GLFWInputSystem();
};

