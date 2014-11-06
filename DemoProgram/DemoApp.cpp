#include "DemoApp.h"


DemoApp::DemoApp() {
	
}


DemoApp::~DemoApp() {
}

void DemoApp::Init(){
	Engine::Init();
	sceneManager->addScene(new Scene());
	scene = sceneManager->getScene(0);
	scene->setRenderer(renderer);

	//Initalize the models
	modelReader = new PLYModelReader();
	modelReader->readModel("Paddle.ply");
	std::vector<GLfloat> cubeVertices = ((PLYModelReader*)modelReader)->getVertices("x", "y", "z");
	std::vector<GLuint> cubeIndices = ((PLYModelReader*)modelReader)->getIndices();
	std::vector<int> indiceCountData = ((PLYModelReader*)modelReader)->getIndiceCountData();
	//Mesh squareMesh = Mesh(squareVertices, squareIndices, "Square");
	Mesh cubeMesh = Mesh(cubeVertices, cubeIndices, "Cube", indiceCountData);
	//meshManager->addMesh(squareMesh);
	meshManager->addMesh(cubeMesh);

	//Initalize the objects, plugging the meshes into them
	cubeObj = new GameObject();
	cubeObj->setMesh(meshManager->getMesh("Cube"));
	//squareObj = new GameObject();
	//squareObj->setMesh(meshManager->getMesh("Square"));

	//Adding the gameobjects to the scene
	//squareObj->setDrawMode(GL_TRIANGLES);
	//squareObj->setPosition(2.0f, 2.0f, -20.0f);
	cubeObj->setVelocity(0.0f, 0, 0);
	scene->addGameObject(cubeObj);
	//scene->addGameObject(squareObj);
}

void DemoApp::OnKeyEvent(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods){
	Engine::OnKeyEvent(_window, _key, _scancode, _action, _mods);
	if (_action == GLFW_PRESS){
		if (_key == GLFW_KEY_A){
			printf("Test");
		} else if (_key == GLFW_KEY_ESCAPE){
			printf("Quit");
		}
	}
	if (_key == GLFW_KEY_LEFT){
		cubeObj->setVelocity(-0.1, 0.0, 0.0);
	}
	if (_key == GLFW_KEY_RIGHT){
		cubeObj->setVelocity(0.1, 0.0, 0.0);
	}
	if (_key == GLFW_KEY_UP){
		cubeObj->setVelocity(0.0, 0.1, 0.0);
	}
	if (_key == GLFW_KEY_DOWN){
		cubeObj->setVelocity(0.0, -0.1, 0.0);
	}
}

void DemoApp::Update(){
	Engine::Update();
	scene->updateGameObjects(gameTime);
}

void DemoApp::Draw(){
	Engine::Draw();
	scene->renderGameObjects();
}
