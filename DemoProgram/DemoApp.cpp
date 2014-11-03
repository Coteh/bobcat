#include "DemoApp.h"


DemoApp::DemoApp() {
	
}


DemoApp::~DemoApp() {
}

void DemoApp::Init(){
	Engine::Init();
	sceneManager->addScene(Scene());
	scene = sceneManager->getScene(0);
	scene->setRenderer(renderer);

	//Initalize the cube and square
	//Cube
	std::vector<GLfloat> cubeVertices{
		1, 1, 1,
		-1, 1, 1,
		-1, -1, 1,
		1, -1, 1,
		1, -1, -1,
		-1, -1, -1,
		-1, 1, -1,
		1, 1, -1
	};
	std::vector<GLuint> cubeIndices{
		0, 1, 2, 2, 3, 0,           // front face
		7, 4, 5, 5, 6, 7,           // back face
		6, 5, 2, 2, 1, 6,           // left face
		7, 0, 3, 3, 4, 7,           // right face
		7, 6, 1, 1, 0, 7,           // top face
		3, 2, 5, 5, 4, 3            // bottom face
	};
	modelReader = new PLYModelReader();
	modelReader->readModel("Cone.ply");
	std::pair<std::vector<GLfloat>, std::vector<GLuint>> modelPair = ((PLYModelReader*)modelReader)->getModelData();
	cubeVertices = modelPair.first;
	cubeIndices = modelPair.second;
	//Square
	//std::vector<GLfloat> squareVertices{
	//	-1, -1, 0,
	//	1, -1, 0,
	//	1, 1, 0,
	//	-1, 1, 0,
	//};
	//std::vector<GLuint> squareIndices{
	//	0, 1, 2, 2, 3, 0            // front face
	//};
	//Mesh squareMesh = Mesh(squareVertices, squareIndices, "Square");
	Mesh cubeMesh = Mesh(cubeVertices, cubeIndices, "Cube");
	//meshManager->addMesh(squareMesh);
	meshManager->addMesh(cubeMesh);

	//Initalize the objects, plugging the meshes into them
	cubeObj = new GameObject();
	cubeObj->setMesh(meshManager->getMesh("Cube"));
	//squareObj = new GameObject();
	//squareObj->setMesh(meshManager->getMesh("Square"));

	//Adding the gameobjects to the scene
	cubeObj->setDrawMode(GL_TRIANGLES);
	//squareObj->setDrawMode(GL_TRIANGLES);
	//squareObj->setPosition(2.0f, 2.0f, -20.0f);
	scene->addGameObject(cubeObj);
	//scene->addGameObject(squareObj);
}

void DemoApp::Update(){
	Engine::Update();
	scene->updateGameObjects(gameTime);
}

void DemoApp::Draw(){
	Engine::Draw();
	scene->renderGameObjects();
}
