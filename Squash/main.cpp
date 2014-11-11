#include <stdio.h>
#include "vgl.h"
#include "SquashApp.h"

Engine* engine;

bool keyWrapper(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods){
	engine->OnKeyEvent(_window, _key, _scancode, _action, _mods);
	return false;
}

void window_size_callback(GLFWwindow* _window, int _width, int _height){
	engine->OnWindowResize(_width, _height);
}

int main(int argc, char const *argv[]) {
	engine = new SquashApp();
	engine->setScreenDimensions(800, 600);
	engine->Init();
	engine->setKeyboardFunc(keyWrapper);
	engine->setWindowSizeFunc(window_size_callback);

	while (engine->getIsGameRunning() && engine->getIsWindowRunning()){
		engine->Update();
		engine->DrawBegin();
		engine->Draw();
		engine->DrawEnd();
	}

	delete engine;
}