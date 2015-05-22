#include "SFMLWindower.h"
#include "OpenGLHelpers.h"

using namespace bobcat;

SFMLWindower::SFMLWindower() {
	logManager = LogManager::getInstance();
	sfEventListener = nullptr;

	//Setting default window settings
	name = "Engine Window (SFML)";
	width = 640;
	height = 640;

	//Setup SFML style
	sfmlWindowStyle = sf::Style::Default;
}

SFMLWindower::~SFMLWindower() {
	delete window;
}

int SFMLWindower::getWidth() {
	return width;
}

int SFMLWindower::getHeight() {
	return height;
}

std::string SFMLWindower::getName() {
	return name;
}

bool SFMLWindower::isVisible() {
	return visibility;
}

bool SFMLWindower::isRunning() {
	return window->isOpen();
}

bool SFMLWindower::isFocused() {
	return isWindowFocused;
}

void SFMLWindower::setWindowDimensions(int _width, int _height) {
	width = _width;
	height = _height;
	if (isOpenGLLoaded){
		glViewport(0, 0, width, height);
	}
	videoMode.width = width;
	videoMode.height = height;
}

void SFMLWindower::setWindowChangedCallback(void* _function) {

}

void SFMLWindower::setName(std::string _name) {
	if (window != nullptr) {
		window->setTitle(_name.c_str());
	}
	name = _name;
}

void SFMLWindower::setWindowStyle(WindowStyle _windowStyle) {
	switch (_windowStyle) {
	case WindowStyle::FULL_SCREEN:
		sfmlWindowStyle = sf::Style::Fullscreen;
		break;
	default: //DEFAULT
		sfmlWindowStyle = sf::Style::Default;
		break;
	}
}

void SFMLWindower::showWindow(int _expression) {
	window->setVisible(_expression);
	visibility = _expression;
}

void SFMLWindower::init() {
	//Initalize a SFML video mode
	videoMode = sf::VideoMode(width, height);

	//Request a Core context
	sf::ContextSettings contextSettings(sf::ContextSettings::Core);

	//Create a SFML window with these window settings
	window = new sf::Window(videoMode, name.c_str(), sfmlWindowStyle, contextSettings);

	if (!window) {
		logManager->log(LogLevel::LOG_ERROR, "Could not initalize SFML window!");
		return;
	} else {
		logManager->log(LogLevel::LOG_INFO, "SFML window initalized successfully!");
	}

	//Loading OpenGL functions
	if (!OpenGLHelpers::loadOpenGL()){
		logManager->log(LogLevel::LOG_ERROR, "OpenGL functions could not load! Exiting...");
		exit(0);
	} else {
		isOpenGLLoaded = true;
	}

	//Initalizing OpenGL Viewport
	glViewport(0, 0, width, height);

	//Print Info of OpenGL and graphics card drivers (for testing)
	OpenGLHelpers::printVersionInfo();

	//Enable the GL Depth Test
	glEnable(GL_DEPTH_TEST);
	//Set GL Depth Function
	glDepthFunc(GL_LESS);

	//TO-DO: Add in v-sync
	//window->setVerticalSyncEnabled(true);

	//SFML window starts out as focused, so set window focused boolean to true
	isWindowFocused = true;
}

void SFMLWindower::updateWindow() {
	sf::Event event;
	while (window->pollEvent(event)){
		if (event.type == sf::Event::Closed) {
			closeWindow();
		} else if (event.type == sf::Event::Resized) {
			setWindowDimensions(event.size.width, event.size.height);
			notifyObservers();
		} else if (event.type == sf::Event::GainedFocus){
			isWindowFocused = true;
		} else if (event.type == sf::Event::LostFocus){
			isWindowFocused = false;
		}
		//Pass the event to the event listener now
		if (sfEventListener != nullptr){
			((void(*)(sf::Event))sfEventListener)(event);
		}
	}
	window->display();
}

void SFMLWindower::notifyObservers() {
	for (size_t i = 0; i < observerFuncVec.size(); i++){
		((void(*)(int, int))observerFuncVec[i])(width, height);
	}
}

void SFMLWindower::closeWindow() {
	window->close();
}