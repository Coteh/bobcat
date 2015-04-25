#pragma once
#include "AbstractWindower.h"
#include "Notifier.h"
#include "LogManager.h"
// Include SFML
#include <SFML\Window.hpp>
// Include OpenGL
#include "vgl.h";

namespace bobcat {

	/**
	* The SFML implementation of AbstractWindower.
	* It is used to interface directly with the SFML windowing system.
	*/
	class SFMLWindower : public AbstractWindower, public Notifier {
		friend class SFMLInputSystem;
	private:
		const char* name;
		int width, height;
		bool visibility;

		LogManager* logManager;

		sf::Context sfmlContext;
		sf::Window* window;
		sf::VideoMode videoMode;

		void* sfEventListener;
	public:
		SFMLWindower();
		~SFMLWindower();

		virtual int getWidth();
		virtual int getHeight();
		virtual const char* getName();
		virtual bool isVisible();
		virtual bool isRunning();
		virtual void setWindowDimensions(int _width, int _height);
		virtual void setWindowChangedCallback(void* _function);
		virtual void setName(const char* _name);
		virtual void showWindow(int _expression);
		virtual void init();
		virtual void updateWindow();
		virtual void closeWindow();

		virtual void notifyObservers();
	};

}