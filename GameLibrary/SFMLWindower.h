#pragma once
#include "AbstractWindower.h"
#include "Notifier.h"
#include "ConfigManager.h"
// Include SFML
#include <SFML\Window.hpp>
// Include OpenGL
#include "vgl.h";

class SFMLWindower : public AbstractWindower, public Notifier {
private:
	const char* name;
	int width, height;
	bool visibility;

	ConfigManager* configManager;
	LogManager* logManager;

	sf::Context sfmlContext;
	sf::Window* window;
	sf::VideoMode videoMode;
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

