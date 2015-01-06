#include "GLFWInputSystem.h"

GLFWInputSystem::GLFWInputSystem(GLFWWindower* _glfwWindower) {
	setGLFWWindower(_glfwWindower);
}

GLFWInputSystem::~GLFWInputSystem() {

}

void GLFWInputSystem::setGLFWWindower(GLFWWindower* _glfwWindower) {
	m_glfwWindower = _glfwWindower;
}

int GLFWInputSystem::translateKeyCodeInput(int _keyCode) {
	switch (_keyCode){
	case InputEnums::KeyCode::KEY_0:			return GLFW_KEY_0;
	case InputEnums::KeyCode::KEY_1:			return GLFW_KEY_1;
	case InputEnums::KeyCode::KEY_2:			return GLFW_KEY_2;
	case InputEnums::KeyCode::KEY_3:			return GLFW_KEY_3;
	case InputEnums::KeyCode::KEY_4:			return GLFW_KEY_4;
	case InputEnums::KeyCode::KEY_5:			return GLFW_KEY_5;
	case InputEnums::KeyCode::KEY_6:			return GLFW_KEY_6;
	case InputEnums::KeyCode::KEY_7:			return GLFW_KEY_7;
	case InputEnums::KeyCode::KEY_8:			return GLFW_KEY_8;
	case InputEnums::KeyCode::KEY_9:			return GLFW_KEY_9;
	case InputEnums::KeyCode::KEY_A:			return GLFW_KEY_A;
	case InputEnums::KeyCode::KEY_B:			return GLFW_KEY_B;
	case InputEnums::KeyCode::KEY_C:			return GLFW_KEY_C;
	case InputEnums::KeyCode::KEY_D:			return GLFW_KEY_D;
	case InputEnums::KeyCode::KEY_E:			return GLFW_KEY_E;
	case InputEnums::KeyCode::KEY_F:			return GLFW_KEY_F;
	case InputEnums::KeyCode::KEY_G:			return GLFW_KEY_G;
	case InputEnums::KeyCode::KEY_H:			return GLFW_KEY_H;
	case InputEnums::KeyCode::KEY_I:			return GLFW_KEY_I;
	case InputEnums::KeyCode::KEY_J:			return GLFW_KEY_J;
	case InputEnums::KeyCode::KEY_K:			return GLFW_KEY_K;
	case InputEnums::KeyCode::KEY_L:			return GLFW_KEY_L;
	case InputEnums::KeyCode::KEY_M:			return GLFW_KEY_M;
	case InputEnums::KeyCode::KEY_N:			return GLFW_KEY_N;
	case InputEnums::KeyCode::KEY_O:			return GLFW_KEY_O;
	case InputEnums::KeyCode::KEY_P:			return GLFW_KEY_P;
	case InputEnums::KeyCode::KEY_Q:			return GLFW_KEY_Q;
	case InputEnums::KeyCode::KEY_R:			return GLFW_KEY_R;
	case InputEnums::KeyCode::KEY_S:			return GLFW_KEY_S;
	case InputEnums::KeyCode::KEY_T:			return GLFW_KEY_T;
	case InputEnums::KeyCode::KEY_U:			return GLFW_KEY_U;
	case InputEnums::KeyCode::KEY_V:			return GLFW_KEY_V;
	case InputEnums::KeyCode::KEY_W:			return GLFW_KEY_W;
	case InputEnums::KeyCode::KEY_X:			return GLFW_KEY_X;
	case InputEnums::KeyCode::KEY_Y:			return GLFW_KEY_Y;
	case InputEnums::KeyCode::KEY_Z:			return GLFW_KEY_Z;
	case InputEnums::KeyCode::KEY_UP:			return GLFW_KEY_UP;
	case InputEnums::KeyCode::KEY_DOWN:			return GLFW_KEY_DOWN;
	case InputEnums::KeyCode::KEY_RIGHT:		return GLFW_KEY_RIGHT;
	case InputEnums::KeyCode::KEY_LEFT:			return GLFW_KEY_LEFT;
	case InputEnums::KeyCode::KEY_PAGE_UP:		return GLFW_KEY_PAGE_UP;
	case InputEnums::KeyCode::KEY_PAGE_DOWN:	return GLFW_KEY_PAGE_DOWN;
	case InputEnums::KeyCode::KEY_BACKSPACE:	return GLFW_KEY_BACKSPACE;
	case InputEnums::KeyCode::KEY_SPACE:		return GLFW_KEY_SPACE;
	case InputEnums::KeyCode::KEY_ESCAPE:		return GLFW_KEY_ESCAPE;
	case InputEnums::KeyCode::KEY_ENTER:		return GLFW_KEY_ENTER;
	}
	return GLFW_KEY_UNKNOWN;
}

int GLFWInputSystem::translateInputStateOutput(int _inputState) {
	switch (_inputState) {
	case GLFW_PRESS:	return InputEnums::InputState::INPUT_PRESSED;
	case GLFW_RELEASE:	return InputEnums::InputState::INPUT_RELEASED;
	case GLFW_REPEAT:	return InputEnums::InputState::INPUT_HELD;
	}
	return InputEnums::InputState::INPUT_NONE;
}

int GLFWInputSystem::getInputState(int _keyCode) {
	int glfwKeyState = m_glfwWindower->getGLFWKeyState(translateKeyCodeInput(_keyCode));
	return translateInputStateOutput(glfwKeyState);
}

bool GLFWInputSystem::isKeyPressed() {
	return m_isKeyPressed;
}

void GLFWInputSystem::GLFWKeyboardEvent(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods){
	m_isKeyPressed = (_action == GLFW_PRESS || _action == GLFW_REPEAT || (_action == GLFW_RELEASE && m_lastKeyAction == GLFW_PRESS) || (_action == GLFW_RELEASE && m_lastKeyAction == GLFW_REPEAT));
	notifyObservers();
	m_lastKeyAction = _action;
}