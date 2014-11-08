#include "DemoApp.h"


DemoApp::DemoApp() {
	
}


DemoApp::~DemoApp() {
}

void DemoApp::Init(){
	Engine::Init();

	/*Setting up Shaders*/
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "square.vert" },
		{ GL_FRAGMENT_SHADER, "square.frag" },
		{ GL_NONE, NULL }
	};

	ShaderInfo shaders2[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL }
	};

	shaderManager->addShader(ShaderLoader::LoadShaders(shaders), "TestShader");
	shaderManager->addShader(ShaderLoader::LoadShaders(shaders2), "TestShader2");
	renderer->SwitchShader(shaderManager->getShader("TestShader2"));

	/*Setting up Scene*/
	sceneManager->addScene(new Scene());
	scene = sceneManager->getScene(0);
	scene->setRenderer(renderer);

	//Initalize the models
	modelReader = new PLYModelReader();
	modelReader->readModel("Torus.ply");
	std::vector<GLfloat> torusVertices = ((PLYModelReader*)modelReader)->getVertices("x", "y", "z");
	std::vector<GLuint> torusIndices = ((PLYModelReader*)modelReader)->getIndices();
	std::vector<int> torusIndiceCountData = ((PLYModelReader*)modelReader)->getIndiceCountData();
	Mesh torusMesh = Mesh(torusVertices, torusIndices, "Torus", torusIndiceCountData);
	meshManager->addMesh(torusMesh);

	modelReader->readModel("TestModel2.ply");
	std::vector<GLfloat> cubeVertices = ((PLYModelReader*)modelReader)->getVertices("x", "y", "z");
	std::vector<GLuint> cubeIndices = ((PLYModelReader*)modelReader)->getIndices();
	std::vector<int> cubeIndiceCountData = ((PLYModelReader*)modelReader)->getIndiceCountData();
	Mesh cubeMesh = Mesh(cubeVertices, cubeIndices, "Cube", cubeIndiceCountData);
	meshManager->addMesh(cubeMesh);

	modelReader->readModel("Circle.ply");
	std::vector<GLfloat> circleVertices = ((PLYModelReader*)modelReader)->getVertices("x", "y", "z");
	std::vector<GLuint> circleIndices = ((PLYModelReader*)modelReader)->getIndices();
	std::vector<int> circleIndiceCountData = ((PLYModelReader*)modelReader)->getIndiceCountData();
	Mesh circleMesh = Mesh(circleVertices, circleIndices, "Circle", circleIndiceCountData);
	meshManager->addMesh(circleMesh);

	//Initalize the objects, plugging the meshes into them
	cubeObj = new GameObject();
	cubeObj->setMesh(meshManager->getMesh("Cube"));
	cubeObj->setPosition(0, -1.5f, 0);
	cubeObj->setVelocity(0.0f, 0.0f, 0.0f);
	cubeObj->setTorque(8.0f);
	scene->addGameObject(cubeObj);

	torusObj = new GameObject();
	torusObj->setMesh(meshManager->getMesh("Torus"));
	torusObj->setPosition(2, 0, 0);
	torusObj->setTorque(8.0f);
	torusObj->setRotAxis(0.0f, 0.0f, 1.0f);
	cubeObj->attachGameObject(torusObj);

	circleObj = new GameObject();
	circleObj->setMesh(meshManager->getMesh("Circle"));
	circleObj->setPosition(-2, 0, 0);
	//circleObj->setTorque(0.0f);
	torusObj->attachGameObject(circleObj);
}

void DemoApp::OnKeyEvent(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods){
	Engine::OnKeyEvent(_window, _key, _scancode, _action, _mods);
	if (_action == GLFW_PRESS){
		if (_key == GLFW_KEY_A){
			printf("Test");
		} else if (_key == GLFW_KEY_ESCAPE){
			printf("Quit");
		} else if (_key == GLFW_KEY_KP_4){
			renderer->SwitchShader(shaderManager->getShader("TestShader2"));
		} else if (_key == GLFW_KEY_KP_6){
			renderer->SwitchShader(shaderManager->getShader("TestShader"));
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
	if (_key == GLFW_KEY_A){
		circleObj->setVelocity(-0.5, 0.0, 0.0);
	}
	if (_key == GLFW_KEY_D){
		circleObj->setVelocity(0.5, 0.0, 0.0);
	}
	if (_key == GLFW_KEY_W){
		circleObj->setVelocity(0.0, 0.5, 0.0);
	}
	if (_key == GLFW_KEY_S){
		circleObj->setVelocity(0.0, -0.5, 0.0);
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
