#include <stdio.h>
#include "vgl.h"
#include "DemoApp.h"

Engine* engine;

void keyWrapper(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods){
	engine->OnKeyEvent(_window, _key, _scancode, _action, _mods);
}

void windowSizeCallback(GLFWwindow* _window, int _width, int _height) {
	engine->OnWindowResize(_window, _width, _height);
}

int main(int argc, char const *argv[]) {
	engine = new DemoApp();
	engine->setScreenDimensions(800, 600);
	engine->Init();
	engine->setKeyboardFunc(keyWrapper);
	engine->setWindowSizeFunc(windowSizeCallback);

	while (engine->getIsGameRunning() && engine->getIsWindowRunning()){
		engine->Update();
		engine->DrawBegin();
		engine->Draw();
		engine->DrawEnd();
	}

	delete engine;
}