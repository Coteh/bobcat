#include "DemoApp.h"


DemoApp::DemoApp() {
	mode = 0;
}

DemoApp::~DemoApp() {
	delete ray;
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

	ShaderLoadInfo shaders4[] = {
		{ GL_VERTEX_SHADER, "colormodel-vert.glsl" },
		{ GL_FRAGMENT_SHADER, "colormodel-frag.glsl" },
		{ GL_NONE, NULL }
	};

	ShaderLoadInfo shaders5[] = {
		{ GL_VERTEX_SHADER, "texturemodel-vert.glsl" },
		{ GL_FRAGMENT_SHADER, "texturemodel-frag.glsl" },
		{ GL_NONE, NULL }
	};

	shaderManager->addShader(ShaderLoader::LoadShaders(shaders), "TestShader");
	shaderManager->addShader(ShaderLoader::LoadShaders(shaders2), "TestShader2");
	shaderManager->addShader(ShaderLoader::LoadShaders(shaders3), "JakeShader");
	shaderManager->addShader(ShaderLoader::LoadShaders(shaders4), "ColorModel");
	shaderManager->addShader(ShaderLoader::LoadShaders(shaders5), "TextureModel");

	/*Setting up Textures*/
	textureManager->loadTexture("kitteh.png", "TestTex");
	Texture* tex = textureManager->getTexture("TestTex");

	/*Setting up Scene*/
	sceneManager->addScene(new Scene());
	scene = sceneManager->getScene(0);
	scene->setRenderer(renderer);

	/*Adding meshes*/
	meshManager->addMesh("Sphere.ply", "Monkey");
	meshManager->addMesh("Cube.ply", "Cube");

	//Initalize the objects, plugging the meshes into them
	cubeObj = new GameObject();
	cubeObj->setMesh(meshManager->getMesh("Monkey"));
	//cubeObj->setTexture(treeTex, st);
	cubeObj->setPosition(0, 0.0f, 0);
	cubeObj->setVelocity(0.0f, 0.0f, 0.0f);
	cubeObj->setShader(shaderManager->getShader("TestShader"));
	cubeObj->setTexture(tex);
	cubeObj->setCollider(new SphereCollider());
	cubeObj->getCollider()->setScale(1.0f);
	cubeObj->setRotationalVel(10.0f, 0.0f, 10.0f);
	scene->addGameObject(cubeObj);
	torusObj = new GameObject();
	torusObj->setMesh(meshManager->getMesh("Cube"));
	torusObj->setPosition(1.0f, 1.0f, -1.0f);
	torusObj->setScale(0.4f, 0.4f, 0.4f);
	torusObj->setShader(shaderManager->getShader("TextureModel"));
	torusObj->setTexture(tex);
	torusObj->setCollider(new SphereCollider());
	torusObj->getCollider()->setScale(2.0f);
	torusObj->setRotationalVel(5.0f, 0.0f, 5.0f);
	scene->addGameObject(torusObj);

	logManager->writeLog(LogLevel::LOG_NONE, "This is a test log");
	logManager->writeLog(LogLevel::LOG_INFO, "This is a test log also");
	logManager->writeLog(LogLevel::LOG_ERROR, "This is an error!");

	renderer->isDebugOn = true;

	camera->attachGameObject(torusObj);

	ray = new Ray(camera->getPosition(), camera->getDirection());
}

void DemoApp::OnKeyEvent(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods){
	Engine::OnKeyEvent(_window, _key, _scancode, _action, _mods);
	if (_action == GLFW_PRESS){
		if (_key == GLFW_KEY_ESCAPE){
			printf("Quit");
			isGameRunning = false;
		} else if (_key == GLFW_KEY_KP_4){
			cubeObj->setShader(shaderManager->getShader("TestShader"));
			torusObj->setShader(shaderManager->getShader("TestShader2"));
		} else if (_key == GLFW_KEY_KP_6){
			cubeObj->setShader(shaderManager->getShader("TestShader2"));
			torusObj->setShader(shaderManager->getShader("TestShader"));
		} else if (_key == GLFW_KEY_1){
			mode = 0;
		} else if (_key == GLFW_KEY_2){
			mode = 1;
		}
	}
}

void DemoApp::OnKeyHandle(){
	Engine::OnKeyHandle();
	//Camera Controls
	if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_W) == GLFW_PRESS){
		camera->Translate(glm::vec3(0.0f, 0.0f, -1.0f) * deltaTime);
	} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_S) == GLFW_PRESS){
		camera->Translate(glm::vec3(0.0f, 0.0f, 1.0f) * deltaTime);
	} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_A) == GLFW_PRESS){
		camera->Rotate(glm::vec3(0.0, 10 * deltaTime, 0.0));
	} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_D) == GLFW_PRESS){
		camera->Rotate(glm::vec3(0.0, -10 * deltaTime, 0.0));
	} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_EQUAL) == GLFW_PRESS){
		camera->IncrementZoom(2.0f * deltaTime);
	} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_MINUS) == GLFW_PRESS){
		camera->IncrementZoom(-2.0f * deltaTime);
	}
	glm::vec3 cubeVelChange = glm::vec3();
	if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_LEFT) == GLFW_PRESS){
		cubeVelChange += glm::vec3(-10.0, 0.0, 0.0);
	}
	if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_RIGHT) == GLFW_PRESS){
		cubeVelChange += glm::vec3(10.0, 0.0, 0.0);
	}
	if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_UP) == GLFW_PRESS){
		cubeVelChange += glm::vec3(0.0, 10.0, 0.0);
	}
	if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_DOWN) == GLFW_PRESS){
		cubeVelChange += glm::vec3(0.0, -10.0, 0.0);
	}
	if (mode){
		camera->setPosition(camera->getPosition() + cubeVelChange * deltaTime);
	} else{
		cubeObj->setPosition(cubeObj->getPosition() + cubeVelChange * deltaTime);
	}
}

void DemoApp::Update(){
	Engine::Update();
	scene->updateGameObjects(deltaTime);
	ray->updateRay(camera->getPosition(), camera->getDirection());
	float dist;
	if (ray->intersects(cubeObj->getCollider()->getPosition(), cubeObj->getCollider()->getRadius(), &dist)){
		printf("Intersects!");
	}
}

void DemoApp::Draw(){
	Engine::Draw();
	scene->renderGameObjects();
}
