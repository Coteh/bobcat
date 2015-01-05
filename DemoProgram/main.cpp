#include <stdio.h>
#include "vgl.h"
#include "DemoApp.h"

#include "GLFWInputSystem.h"

Engine* engine;

void keyListener(){
	engine->OnKeyEvent();
}

void onWindowChanged(int _width, int _height){
	engine->OnWindowResize(_width, _height);
}

int main(int argc, char const *argv[]) {
	engine = new DemoApp(ENGINE_INIT);
	engine->setKeyboardCallback(GLFWInputSystem::GLFWKeyFun);
	engine->getInputSystem()->registerListener(keyListener);
	engine->setWindowChangedCallback(GLFWWindower::GLFWWindowSizeCallback);
	((GLFWWindower*)engine->getWindower())->registerListener(onWindowChanged);

	engine->Run();

	delete engine;
}