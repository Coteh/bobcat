#pragma once
#include "AbstractNotifier.h"
#include <string>

#define WINDOW_SHOW 1
#define WINDOW_HIDE 0

namespace bobcat {

	struct WindowSettings {
		int windowWidth;
		int windowHeight;
		const char* windowName;
		const char* windowStyle;
	};

	//TO DO
	//Put enums in namespaces (maybe?)
	enum WindowStyle {
		NO_WINDOW_STYLE, DEFAULT, FULL_SCREEN
	};

	/**
	* An abstract class that all Windowers must derive from and use.
	* Windowers have methods that allow for direct interfacing
	* with windowing systems.
	*/
	class AbstractWindower : public virtual AbstractNotifier {
	public:
		/**
		* Returns the width of a window.
		*/
		virtual int getWidth() = 0;

		/**
		* Returns the height of a window.
		*/
		virtual int getHeight() = 0;

		/**
		* Returns the name of a window.
		*/
		virtual std::string getName() = 0;

		/**
		* Returns a bool indicating whether the window is visible or not.
		*/
		virtual bool isVisible() = 0;

		/**
		* Returns a bool indicating whether the window is running or not.
		*/
		virtual bool isRunning() = 0;

		virtual bool isFocused() = 0;

		/**
		* Set window dimensions. (width and height)
		*/
		virtual void setWindowDimensions(int _width, int _height) = 0;

		/**
		* Set window name.
		*/
		virtual void setName(std::string _name) = 0;

		virtual void setWindowStyle(WindowStyle _windowStyle) = 0;

		/**
		* Toggle window visibility.
		*/
		virtual void showWindow(int _expression) = 0;

		/**
		* Initalize the window.
		*/
		virtual void init() = 0;

		/**
		* Window update call. Usually called after rendering
		* is completed so that it can swap buffers and/or poll events.
		*/
		virtual void updateWindow() = 0;

		/**
		* Close the window.
		*/
		virtual void closeWindow() = 0;

		virtual ~AbstractWindower(){}
	};

}