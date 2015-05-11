#include <stdio.h>
#include "BobcatDemo.h"

bobcat::Engine* engine;

void keyListener(){
	engine->OnKeyEvent();
}

void onWindowChanged(int _width, int _height){
	engine->OnWindowResize(_width, _height);
}

int main(int argc, char const *argv[]) {
	engine = new BobcatDemo(ENGINE_INIT);
	engine->getInputSystem()->registerObserver(keyListener);
	engine->getWindower()->registerObserver(onWindowChanged);

	engine->Run();

	delete engine;
}