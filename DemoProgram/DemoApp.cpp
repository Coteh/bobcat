#include "DemoApp.h"
#include <glm\gtc\type_ptr.hpp>

#define TEXTURE_MODEL "TextureModel"

DemoApp::DemoApp() {
	mode = 0;
	renderMode = 0;
}

DemoApp::DemoApp(int _engineCmd) : DemoApp(){
	if (_engineCmd){
		Init();
	}
}

DemoApp::~DemoApp() {
	delete ray;
	delete mat;
	delete noTexMat;
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

	ShaderLoadInfo shaders6[] = {
		{ GL_VERTEX_SHADER, "thomasalex-vert.glsl" },
		{ GL_FRAGMENT_SHADER, "uniformcolor-frag.glsl" },
		{ GL_NONE, NULL }
	};

	shaderManager->addShader(ShaderLoader::LoadShaders(shaders), "TestShader");
	shaderManager->addShader(ShaderLoader::LoadShaders(shaders2), "TestShader2");
	shaderManager->addShader(ShaderLoader::LoadShaders(shaders3), "JakeShader");
	shaderManager->addShader(ShaderLoader::LoadShaders(shaders4), "ColorModel");
	shaderManager->addShader(ShaderLoader::LoadShaders(shaders5), "TextureModel");
	shaderManager->addShader(ShaderLoader::LoadShaders(shaders6), "UniformColor");

	/*Setting up Textures*/
	resourceManager->loadTexture("kitteh.png", "Moon");
	resourceManager->loadTexture("OrangeLand.png", "OrangeLand");
	Texture* tex = resourceManager->getTexture("Moon");
	Texture* planeTex = resourceManager->getTexture("OrangeLand");

	/*Setting up Scene*/
	sceneManager->addScene(new Scene());
	scene = sceneManager->getScene(0);
	scene->setRenderer(renderer);

	/*Adding meshes*/
	resourceManager->addMesh("Sphere.ply", "Sphere");
	resourceManager->addMesh("Monkey.ply", "Monkey");
	resourceManager->addMesh("Plane.ply", "Plane");
	resourceManager->addMesh("Cube.ply", "Cube");

	/*Adding Materials*/
	mat = new Material();
	mat->color = glm::vec4(1.0, 0.0, 0.0, 1.0);
	mat->shader = shaderManager->getShader(TEXTURE_MODEL);
	mat->texture = tex;
	noTexMat = new Material();
	noTexMat->color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	noTexMat->shader = shaderManager->getShader("UniformColor");

	//Initalize the objects, plugging the meshes into them
	GameObjectConstructionInfo cubeObjInfo;
	cubeObjInfo.setTransformValues();
	cubeObjInfo.setColliderMode(ColliderMode::SPHERE);
	cubeObjInfo.setRigidbodyValues(glm::vec3(0.0f), glm::vec3(10.0f, 0.0f, 10.0f), 1.0f);
	cubeObjInfo.setMesh(resourceManager->getMesh("Sphere"));
	cubeObj = GameObjectCreator::ConstructFrom(cubeObjInfo);
	cubeObj->renderer->material = mat;
	sphereTorque = cubeObj->rigidbody->rotationalVel;
	scene->addGameObject(cubeObj);

	GameObjectConstructionInfo torusObjInfo;
	torusObjInfo.setTransformValues(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.4f));
	torusObjInfo.setColliderMode(ColliderMode::BOX);
	torusObjInfo.setRigidbodyValues(glm::vec3(0.0f), glm::vec3(5.0f, 0.0f, 5.0f), 1.0f);
	torusObjInfo.setMesh(resourceManager->getMesh("Cube"));
	torusObj = GameObjectCreator::ConstructFrom(torusObjInfo);
	torusObj->renderer->material = mat;
	scene->addGameObject(torusObj);

	GameObjectConstructionInfo circleObjInfo;
	circleObjInfo.setTransformValues(glm::vec3(20.0f, 1.0f, 1.0f), glm::vec3(0.0f), glm::vec3(0.4f));
	circleObjInfo.setColliderMode(ColliderMode::BOX);
	circleObjInfo.setRigidbodyValues(glm::vec3(0.0f), glm::vec3(10.0f, 0.0f, 10.0f), 1.0f);
	circleObjInfo.setMesh(resourceManager->getMesh("Monkey"));
	circleObj = GameObjectCreator::ConstructFrom(circleObjInfo);
	circleObj->renderer->material = mat;
	scene->addGameObject(circleObj);

	GameObjectConstructionInfo planeObjInfo;
	planeObjInfo.setTransformValues(glm::vec3(0.0f, -10.0f, -10.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(100.0f, 100.0f, 100.0f));
	planeObjInfo.setMesh(resourceManager->getMesh("Plane"));
	planeObj = GameObjectCreator::ConstructFrom(planeObjInfo);
	planeObj->renderer->material = mat;
	scene->addGameObject(planeObj);
	printf("%d", planeObj->AddComponent<TestComponent>()->testNum);

	logManager->writeLog(LogLevel::LOG_NONE, "This is a test log");
	logManager->writeLog(LogLevel::LOG_INFO, "This is a test log also");
	logManager->writeLog(LogLevel::LOG_ERROR, "This is an error!");

	camera->setPosition(glm::vec3(0, 0, 20));
	origCameraPos = camera->getPosition();
	camera->attachGameObject(torusObj);

	lightSource = glm::vec3(0.0, -10.0, -1000.0);

	ray = new Ray(camera->getPosition(), camera->getForward());

	renderer->setDebugRender(debugRenderOn);
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
			debugRenderOn = !debugRenderOn;
			renderer->setDebugRender(debugRenderOn);
		} else if (_key == GLFW_KEY_Y){
			renderMode = !renderMode;
			if (renderMode){
				cubeObj->renderer->material = noTexMat;
				torusObj->renderer->material = noTexMat;
				circleObj->renderer->material = noTexMat;
				planeObj->renderer->material = noTexMat;
			} else{
				cubeObj->renderer->material = mat;
				torusObj->renderer->material = mat;
				circleObj->renderer->material = mat;
				planeObj->renderer->material = mat;
			}
		} else if (_key == GLFW_KEY_C){
			planeObj->RemoveComponent<TestComponent>();
		}
	}
}

void DemoApp::OnKeyHandle(){
	Engine::OnKeyHandle();
	switch (mode){
	case 0:
		//Camera Controls
		if (((GLFWWindower*)window)->getGLFWKeyState(GLFW_KEY_UP) == GLFW_PRESS){
			camera->Translate(-50.0f * camera->getForward() * deltaTime);
		} else if (((GLFWWindower*)window)->getGLFWKeyState(GLFW_KEY_DOWN) == GLFW_PRESS){
			camera->Translate(50.0f * camera->getForward() * deltaTime);
		} else if (((GLFWWindower*)window)->getGLFWKeyState(GLFW_KEY_LEFT) == GLFW_PRESS){
			camera->Translate(-50.0f * camera->getRight() * deltaTime);
		} else if (((GLFWWindower*)window)->getGLFWKeyState(GLFW_KEY_RIGHT) == GLFW_PRESS){
			camera->Translate(50.0f * camera->getRight() * deltaTime);
		}
		if (((GLFWWindower*)window)->getGLFWKeyState(GLFW_KEY_A) == GLFW_PRESS){
			camera->Rotate(glm::vec3(0.0f, 100.0f, 0.0f) * deltaTime);
		} else if (((GLFWWindower*)window)->getGLFWKeyState(GLFW_KEY_D) == GLFW_PRESS){
			camera->Rotate(glm::vec3(0.0f, -100.0f, 0.0f) * deltaTime);
		} else if (((GLFWWindower*)window)->getGLFWKeyState(GLFW_KEY_W) == GLFW_PRESS){
			camera->Rotate(glm::vec3(100.0f, 0.0f, 0.0f) * deltaTime);
		} else if (((GLFWWindower*)window)->getGLFWKeyState(GLFW_KEY_S) == GLFW_PRESS){
			camera->Rotate(glm::vec3(-100.0f, 0.0f, 0.0f) * deltaTime);
		} else if (((GLFWWindower*)window)->getGLFWKeyState(GLFW_KEY_R) == GLFW_PRESS){
			camera->setPosition(origCameraPos);
			camera->setRotationEuler(glm::vec3(0.0f, 0.0f, -1.0f));
		}
		break;
	case 1:
		//Sphere Controls
		if (((GLFWWindower*)window)->getGLFWKeyState(GLFW_KEY_UP) == GLFW_PRESS){
			cubeObj->transform->position = cubeObj->transform->position + glm::vec3(0.0f, 50.0f, 0.0f) * deltaTime;
		} else if (((GLFWWindower*)window)->getGLFWKeyState(GLFW_KEY_DOWN) == GLFW_PRESS){
			cubeObj->transform->position = cubeObj->transform->position + glm::vec3(0.0f, -50.0f, 0.0f) * deltaTime;
		} else if (((GLFWWindower*)window)->getGLFWKeyState(GLFW_KEY_LEFT) == GLFW_PRESS){
			cubeObj->transform->position = cubeObj->transform->position + glm::vec3(-50.0f, 0.0f, 0.0f) * deltaTime;
		} else if (((GLFWWindower*)window)->getGLFWKeyState(GLFW_KEY_RIGHT) == GLFW_PRESS){
			cubeObj->transform->position = cubeObj->transform->position + glm::vec3(50.0f, 0.0f, 0.0f) * deltaTime;
		} else if (((GLFWWindower*)window)->getGLFWKeyState(GLFW_KEY_R) == GLFW_PRESS){
			cubeObj->transform->position = sphereOrigPos;
			cubeObj->transform->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		}
		break;
	}
}

void DemoApp::Update(){
	Engine::Update();
	scene->updateGameObjects(deltaTime);
	ray->updateRay(camera->getPosition(), camera->getForward());
	float dist;
	Collider* col = cubeObj->collider;
	/*if (ray->intersects(col->getPosition(), col->getRadius() * col->getScale(), &dist)){
		//Something will happen here
	}else{
		//Something else will happen here
	}*/
	if (shaderManager->getCurrShader() != nullptr){
		glUniform3fv(shaderManager->getCurrShader()->lightingLoc, 1, glm::value_ptr(lightSource));
	}
}

void DemoApp::Draw(){
	Engine::Draw();
	scene->renderGameObjects();
}
