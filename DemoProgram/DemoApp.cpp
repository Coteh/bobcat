#include "DemoApp.h"


DemoApp::DemoApp() {
	
}


DemoApp::~DemoApp() {
}

void DemoApp::Init(){
	Engine::Init();

	/*Setting up Shaders*/
	ShaderLoadInfo shaders[] = {
		{ GL_VERTEX_SHADER, "rainbow-vert.glsl" },
		{ GL_FRAGMENT_SHADER, "rainbow-frag.glsl" },
		{ GL_NONE, NULL }
	};

	ShaderLoadInfo shaders2[] = {
		{ GL_VERTEX_SHADER, "thomasalex-vert.glsl" },
		{ GL_FRAGMENT_SHADER, "thomasalex-frag.glsl" },
		{ GL_NONE, NULL }
	};

	ShaderLoadInfo shaders3[] = {
		{ GL_VERTEX_SHADER, "SimpleVertexShader.glsl" },
		{ GL_FRAGMENT_SHADER, "SimpleFragmentShader.glsl" },
		{ GL_NONE, NULL }
	};

	shaderManager->addShader(ShaderLoader::LoadShaders(shaders), "TestShader");
	shaderManager->addShader(ShaderLoader::LoadShaders(shaders2), "TestShader2");
	shaderManager->addShader(ShaderLoader::LoadShaders(shaders3), "JakeShader");
	shaderManager->useShader("TestShader");

	/*Setting up Textures*/
	textureManager->loadTexture("de1.tga", "treeTexture");
	Texture* treeTex = &textureManager->getTexture("treeTexture");

	/*std::vector<GLfloat> st{
		0.25f, 0.66f, 0.25f, 0.33f, 0.0f, 0.33f, 0.0f, 0.66f,
		0.5f, 0.66f, 0.5f, 0.33f, 0.25f, 0.33f, 0.25f, 0.66f,
		0.75f, 0.66f, 0.75f, 0.33f, 0.5f, 0.33f, 0.5f, 0.66f,
		1.0f, 0.66f, 1.0f, 0.33f, 0.75f, 0.33f, 0.75f, 0.66f,
		0.75f, 0.33f, 0.75f, 0.0f, 0.5f, 0.0f, 0.5f, 0.33f,
		0.75f, 1.0f, 0.75f, 0.66f, 0.5f, 0.66f, 0.5f, 1.0f
	};*/

	/*Setting up Scene*/
	sceneManager->addScene(new Scene());
	scene = sceneManager->getScene(0);
	scene->setRenderer(renderer);

	//Initalize the models
	modelReader = new PLYModelReader();
	/*modelReader->readModel("Torus.ply");
	std::vector<GLfloat> torusVertices = ((PLYModelReader*)modelReader)->getVertices("x", "y", "z");
	std::vector<GLuint> torusIndices = ((PLYModelReader*)modelReader)->getIndices();
	std::vector<int> torusIndiceCountData = ((PLYModelReader*)modelReader)->getIndiceCountData();
	Mesh torusMesh = Mesh(torusVertices, torusIndices, "Torus", torusIndiceCountData);
	meshManager->addMesh(torusMesh);*/

	modelReader->readModel("Torus.ply");
	std::vector<GLfloat> cubeVertices = ((PLYModelReader*)modelReader)->getAllVertexData();
	std::vector<GLuint> cubeIndices = ((PLYModelReader*)modelReader)->getIndices();
	std::vector<int> cubeIndiceCountData = ((PLYModelReader*)modelReader)->getIndiceCountData();
	Mesh cubeMesh = Mesh(cubeVertices, cubeIndices, "Cube", cubeIndiceCountData, shaderManager->getShader("TestShader"));
	//cubeMesh.setShader(shaderManager->getShader("TestShader"));
	meshManager->addMesh(cubeMesh);

	/*modelReader->readModel("Circle.ply");
	std::vector<GLfloat> circleVertices = ((PLYModelReader*)modelReader)->getVertices("x", "y", "z");
	std::vector<GLuint> circleIndices = ((PLYModelReader*)modelReader)->getIndices();
	std::vector<int> circleIndiceCountData = ((PLYModelReader*)modelReader)->getIndiceCountData();
	Mesh circleMesh = Mesh(circleVertices, circleIndices, "Circle", circleIndiceCountData);
	meshManager->addMesh(circleMesh);*/

	//Initalize the objects, plugging the meshes into them
	cubeObj = new GameObject();
	cubeObj->setMesh(meshManager->getMesh("Cube"));
	//cubeObj->setTexture(treeTex, st);
	cubeObj->setPosition(0, 0.0f, 0);
	cubeObj->setVelocity(0.0f, 0.0f, 0.0f);
	scene->addGameObject(cubeObj);
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
	glm::vec3 cubePos = cubeObj->getPosition();
	glm::vec3 cubeVelChange = glm::vec3();
	if (_key == GLFW_KEY_LEFT){
		cubeVelChange += glm::vec3(-1.0, 0.0, 0.0);
	}
	if (_key == GLFW_KEY_RIGHT){
		cubeVelChange += glm::vec3(1.0, 0.0, 0.0);
	}
	if (_key == GLFW_KEY_UP){
		cubeVelChange += glm::vec3(0.0, 1.0, 0.0);
	}
	if (_key == GLFW_KEY_DOWN){
		cubeVelChange += glm::vec3(0.0, -1.0, 0.0);
	}
	cubeObj->setPosition(cubePos + cubeVelChange * gameTime);
}

void DemoApp::OnKeyHandle(){
	Engine::OnKeyHandle();
	//Camera Controls
	if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_EQUAL) == GLFW_PRESS){
		camera->IncrementZoom(-2.0f * gameTime);
	} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_MINUS) == GLFW_PRESS){
		camera->IncrementZoom(2.0f * gameTime);
	}
}

void DemoApp::Update(){
	Engine::Update();
	scene->updateGameObjects(gameTime);
	glm::vec3 rot = cubeObj->getRotation();
	cubeObj->setRotationEuler(rot.x + (10.0f * gameTime), rot.y + (0.0f * gameTime), rot.z + (10.0f * gameTime));
}

void DemoApp::Draw(){
	Engine::Draw();
	scene->renderGameObjects();
}
