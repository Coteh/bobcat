#include "DemoApp.h"
#include <glm\gtc\type_ptr.hpp>

#define TEXTURE_MODEL "TextureModel"

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
	resourceManager->loadTexture("kitteh.png", "TestTex");
	resourceManager->loadTexture("Moon.png", "Moon");
	Texture* tex = resourceManager->getTexture("TestTex");
	Texture* planeTex = resourceManager->getTexture("Moon");

	/*Setting up Scene*/
	sceneManager->addScene(new Scene());
	scene = sceneManager->getScene(0);
	scene->setRenderer(renderer);

	/*Adding meshes*/
	resourceManager->addMesh("Sphere.ply", "Monkey");
	resourceManager->addMesh("Monkey.ply", "Cube");
	resourceManager->addMesh("Plane.ply", "Plane");

	//Initalize the objects, plugging the meshes into them
	cubeObj = new GameObject();
	cubeObj->setMesh(resourceManager->getMesh("Monkey"));
	cubeObj->setPosition(0, 0.0f, 0);
	sphereOrigPos = cubeObj->getPosition();
	cubeObj->setVelocity(0.0f, 0.0f, 0.0f);
	cubeObj->setShader(shaderManager->getShader("TestShader"));
	cubeObj->setTexture(tex);
	cubeObj->setCollider(new SphereCollider());
	cubeObj->getCollider()->setScale(1.0f);
	cubeObj->setRotationalVel(10.0f, 0.0f, 10.0f);
	sphereTorque = cubeObj->getRotationalVel();
	scene->addGameObject(cubeObj);
	torusObj = new GameObject();
	torusObj->setMesh(resourceManager->getMesh("Cube"));
	torusObj->setPosition(1.0f, 1.0f, -1.0f);
	torusObj->setScale(0.4f, 0.4f, 0.4f);
	torusObj->setShader(shaderManager->getShader("TestShader"));
	torusObj->setTexture(tex);
	torusObj->setCollider(new BoxCollider());
	torusObj->getCollider()->setScale(1.0f);
	torusObj->getCollider()->setDimensions(1.0f, 1.0f, 1.0f);
	torusObj->setRotationalVel(5.0f, 0.0f, 5.0f);
	scene->addGameObject(torusObj);

	torusObj = new GameObject();
	torusObj->setMesh(resourceManager->getMesh("Cube"));
	torusObj->setPosition(20.0f, 1.0f, 1.0f);
	torusObj->setScale(0.4f, 0.4f, 0.4f);
	torusObj->setShader(shaderManager->getShader("TestShader"));
	//torusObj->setTexture(tex);
	torusObj->setCollider(new BoxCollider());
	torusObj->getCollider()->setScale(1.0f);
	torusObj->getCollider()->setDimensions(1.0f, 1.0f, 1.0f);
	torusObj->setRotationalVel(10.0f, 0.0f, 10.0f);
	scene->addGameObject(torusObj);

	GameObject* planeObj = new GameObject();
	planeObj->setMesh(resourceManager->getMesh("Plane"));
	planeObj->setPosition(glm::vec3(0.0f, -10.0f, -10.0f));
	planeObj->setRotationEuler(90.0f, 0.0f, 0.0f);
	planeObj->setScale(100.0f, 100.0f, 100.0f);
	planeObj->setShader(shaderManager->getShader(TEXTURE_MODEL));
	planeObj->setTexture(planeTex);
	scene->addGameObject(planeObj);

	logManager->writeLog(LogLevel::LOG_NONE, "This is a test log");
	logManager->writeLog(LogLevel::LOG_INFO, "This is a test log also");
	logManager->writeLog(LogLevel::LOG_ERROR, "This is an error!");

	camera->setPosition(glm::vec3(0, 0, 20));
	origCameraPos = camera->getPosition();
	camera->attachGameObject(torusObj);

	lightSource = glm::vec3(-10.0, 10.0, -10.0);

	ray = new Ray(camera->getPosition(), camera->getForward());
}

void DemoApp::OnKeyEvent(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods){
	Engine::OnKeyEvent(_window, _key, _scancode, _action, _mods);
	if (_action == GLFW_PRESS){
		if (_key == GLFW_KEY_ESCAPE){
			printf("Quit");
			isGameRunning = false;
		} else if (_key == GLFW_KEY_1){
			mode = 0;
		} else if (_key == GLFW_KEY_2){
			mode = 1;
		} else if (_key == GLFW_KEY_U){
			renderer->isDebugOn = !renderer->isDebugOn;
		}
	}
}

void DemoApp::OnKeyHandle(){
	Engine::OnKeyHandle();
	switch (mode){
	case 0:
		//Camera Controls
		if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_UP) == GLFW_PRESS){
			camera->Translate(-50.0f * camera->getForward() * deltaTime);
		} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_DOWN) == GLFW_PRESS){
			camera->Translate(50.0f * camera->getForward() * deltaTime);
		} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_LEFT) == GLFW_PRESS){
			camera->Translate(-50.0f * camera->getRight() * deltaTime);
		} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_RIGHT) == GLFW_PRESS){
			camera->Translate(50.0f * camera->getRight() * deltaTime);
		}
		if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_A) == GLFW_PRESS){
			camera->Rotate(glm::vec3(0.0f, 100.0f, 0.0f) * deltaTime);
		} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_D) == GLFW_PRESS){
			camera->Rotate(glm::vec3(0.0f, -100.0f, 0.0f) * deltaTime);
		} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_W) == GLFW_PRESS){
			camera->Rotate(glm::vec3(100.0f, 0.0f, 0.0f) * deltaTime);
		} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_S) == GLFW_PRESS){
			camera->Rotate(glm::vec3(-100.0f, 0.0f, 0.0f) * deltaTime);
		} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_R) == GLFW_PRESS){
			camera->setPosition(origCameraPos);
			camera->setRotationEuler(glm::vec3(0.0f, 0.0f, -1.0f));
		}
		break;
	case 1:
		//Sphere Controls
		if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_UP) == GLFW_PRESS){
			cubeObj->setPosition(cubeObj->getPosition() + glm::vec3(-50.0f, 0.0f, 0.0f) * deltaTime);
		} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_DOWN) == GLFW_PRESS){
			cubeObj->setPosition(cubeObj->getPosition() + glm::vec3(-50.0f, 0.0f, 0.0f) * deltaTime);
		} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_LEFT) == GLFW_PRESS){
			cubeObj->setPosition(cubeObj->getPosition() + glm::vec3(-50.0f, 0.0f, 0.0f) * deltaTime);
		} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_RIGHT) == GLFW_PRESS){
			cubeObj->setPosition(cubeObj->getPosition() + glm::vec3(-50.0f, 0.0f, 0.0f) * deltaTime);
		} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_R) == GLFW_PRESS){
			cubeObj->setPosition(sphereOrigPos);
			cubeObj->setRotationEuler(glm::vec3(0.0f, 0.0f, 0.0f));
		}
		break;
	}
}

void DemoApp::Update(){
	Engine::Update();
	scene->updateGameObjects(deltaTime);
	ray->updateRay(camera->getPosition(), camera->getForward());
	float dist;
	Collider* col = cubeObj->getCollider();
	/*if (ray->intersects(col->getPosition(), col->getRadius() * col->getScale(), &dist)){
		cubeObj->setShader(shaderManager->getShader("TestShader2"));
	}else{
		cubeObj->setShader(shaderManager->getShader(TEXTURE_MODEL));
	}*/
	if (shaderManager->getCurrShader() != nullptr){
		glUniform3fv(shaderManager->getCurrShader()->lightingLoc, 1, glm::value_ptr(lightSource));
	}
}

void DemoApp::Draw(){
	Engine::Draw();
	scene->renderGameObjects();
}
