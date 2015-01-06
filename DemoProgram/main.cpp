#include <stdio.h>
#include "vgl.h"
#include "DemoApp.h"

Engine* engine;

void keyListener(){
	engine->OnKeyEvent();
}

void onWindowChanged(int _width, int _height){
	engine->OnWindowResize(_width, _height);
}

int main(int argc, char const *argv[]) {
	engine = new DemoApp(ENGINE_INIT);
	engine->getInputSystem()->registerObserver(keyListener);
	engine->getWindower()->registerObserver(onWindowChanged);

	engine->Run();

	delete engine;
}