#pragma once
#include "AbstractWindower.h"
#include "Notifier.h"
#include "LogManager.h"
// Include OpenGL
#include "External\gl_core_3_3.h"
// Include GLFW
#include <GLFW\glfw3.h>

namespace bobcat {

	/**
	* The GLFW implementation of AbstractWindower.
	* It is used to interface directly with the GLFW windowing system.
	*/
	class GLFWWindower : public AbstractWindower, public Notifier {
		friend class GLFWInputSystem;
		friend class GLFWAPIHolder;
	public:
		GLFWWindower();
		virtual ~GLFWWindower();
		virtual int getWidth();
		virtual int getHeight();
		virtual std::string getName();
		virtual bool isVisible();
		virtual bool isRunning();
		virtual bool isFocused();
		virtual void setWindowDimensions(int _width, int _height);
		virtual void setName(std::string _name);
		virtual void setWindowStyle(WindowStyle _windowStyle);
		virtual void showWindow(int _expression);
		virtual void init();
		virtual void updateWindow();
		virtual void closeWindow();

		/**
		* Receives the Window Changed callback from the GLFW API.
		*/
		void OnWindowChanged(GLFWwindow* _window, int _width, int _height);
	protected:
		/**
		* Get GLFW-specific key state of supplied key.
		* @note This is used to supply key state information to GLFWInputSystem.
		*/
		int getGLFWKeyState(int _key);

		virtual void notifyObservers();
	private:
		GLFWwindow* window;
		std::string name;
		int width, height;
		bool isWindowFocused;
		LogManager* logManager;
		bool isOpenGLLoaded;
	};

}