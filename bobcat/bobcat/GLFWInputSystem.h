#pragma once
#include "AbstractInputSystem.h"
#include "Notifier.h"
#include "GLFWWindower.h"
#include <vector>

namespace bobcat {

	/**
	* The GLFW implementation of AbstractInputSystem.
	* It is used to interface directly with the input portion of the GLFW windowing system.
	*/
	class GLFWInputSystem : public AbstractInputSystem, public Notifier {
	private:
		GLFWWindower* m_glfwWindower;
		bool m_isKeyPressed;
		int m_lastKeyAction;
	protected:
		virtual int translateKeyCodeInput(int _keyCode);
		virtual int translateInputStateOutput(int _inputState);
	public:
		/**
		* Default constructor for GLFWInputSystem.
		* Provide a pointer to GLFWWindower that this input system can use.
		* @note The GLFWWindower instance is used to get the input state for a key from the GLFWwindow instance (Not to be confused with GLFWWindower) within it.
		*/
		GLFWInputSystem(GLFWWindower* _glfwWindower);

		/**
		* Set the GLFWWindower reference to be used by this GLFWInputSystem.
		*/
		void setGLFWWindower(GLFWWindower* _glfwWindower);

		/**
		* Receives the Keyboard callback from the GLFW API.
		*/
		void GLFWKeyboardEvent(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);

		virtual int getInputState(int _keyCode);

		virtual bool isKeyPressed();

		virtual ~GLFWInputSystem();
	};

}