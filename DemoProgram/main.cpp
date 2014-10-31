#include <stdio.h>
#include "vgl.h"
#include "DemoApp.h"

Engine* engine;

int main(int argc, char const *argv[]) {
	engine = new DemoApp();
	engine->setScreenDimensions(800, 600);
	engine->Init();

	while (engine->getGameRunning() && engine->getWindowRunning()){
		engine->Update();
		engine->DrawBegin();
		engine->Draw();
		engine->DrawEnd();
	}

	delete engine;
}