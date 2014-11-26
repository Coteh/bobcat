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

	/*Setting up Textures*/
	textureManager->loadTexture("de1.tga", "treeTexture");
	Texture* treeTex = &textureManager->getTexture("treeTexture");

	/*Setting up Scene*/
	sceneManager->addScene(new Scene());
	scene = sceneManager->getScene(0);
	scene->setRenderer(renderer);

	/*Adding meshes*/
	meshManager->addMesh("Sphere.ply", "Monkey");
	meshManager->addMesh("TestModel2.ply", "Cube");

	//Initalize the objects, plugging the meshes into them
	cubeObj = new GameObject();
	cubeObj->setMesh(meshManager->getMesh("Monkey"));
	//cubeObj->setTexture(treeTex, st);
	cubeObj->setPosition(0, 0.0f, 0);
	cubeObj->setVelocity(0.0f, 0.0f, 0.0f);
	cubeObj->setShader(shaderManager->getShader("TestShader"));
	torusObj = new GameObject();
	torusObj->setMesh(meshManager->getMesh("Cube"));
	torusObj->setPosition(1.0f, 1.0f, -1.0f);
	torusObj->setScale(0.4f, 0.4f, 0.4f);
	torusObj->setShader(shaderManager->getShader("TestShader2"));
	torusObj->setCollider(new SphereCollider());
	torusObj->getCollider()->setScale(2.0f);
	scene->addGameObject(cubeObj);
	scene->addGameObject(torusObj);

	logManager->writeLog(LogLevel::LOG_INFO, "This is a test log");
	logManager->writeLog(LogLevel::LOG_INFO, "This is a test log also");
	logManager->writeLog(LogLevel::LOG_ERROR, "This is an error!");

	renderer->isDebugOn = true;
}

void DemoApp::OnKeyEvent(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods){
	Engine::OnKeyEvent(_window, _key, _scancode, _action, _mods);
	if (_action == GLFW_PRESS){
		if (_key == GLFW_KEY_ESCAPE){
			printf("Quit");
		} else if (_key == GLFW_KEY_KP_4){
			cubeObj->setShader(shaderManager->getShader("TestShader"));
			torusObj->setShader(shaderManager->getShader("TestShader2"));
		} else if (_key == GLFW_KEY_KP_6){
			cubeObj->setShader(shaderManager->getShader("TestShader2"));
			torusObj->setShader(shaderManager->getShader("TestShader"));
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
	cubeObj->setPosition(cubePos + cubeVelChange * deltaTime);
}

void DemoApp::OnKeyHandle(){
	Engine::OnKeyHandle();
	//Camera Controls
	if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_W) == GLFW_PRESS){
		camera->Translate(glm::vec3(0.0f, 0.0f, -1.0f) * deltaTime);
	} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_S) == GLFW_PRESS){
		camera->Translate(glm::vec3(0.0f, 0.0f, 1.0f) * deltaTime);
	} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_A) == GLFW_PRESS){
		camera->Rotate(glm::vec3(-0.001, 0.0, 0.0));
	} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_D) == GLFW_PRESS){
		camera->Rotate(glm::vec3(0.001, 0.0, 0.0));
	} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_EQUAL) == GLFW_PRESS){
		camera->IncrementZoom(2.0f * deltaTime);
	} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_MINUS) == GLFW_PRESS){
		camera->IncrementZoom(-2.0f * deltaTime);
	}
}

void DemoApp::Update(){
	Engine::Update();
	scene->updateGameObjects(deltaTime);
	glm::vec3 rot = cubeObj->getRotation();
	cubeObj->setRotationEuler(rot.x + (10.0f * deltaTime), rot.y + (0.0f * deltaTime), rot.z + (10.0f * deltaTime));
	torusObj->setRotationEuler(rot.x + (5.0f * deltaTime), rot.y + (0.0f * deltaTime), rot.z + (5.0f * deltaTime));
}

void DemoApp::Draw(){
	Engine::Draw();
	scene->renderGameObjects();
}
