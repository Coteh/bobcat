#include "DemoApp.h"
#include <glm\gtc\type_ptr.hpp>

#define TEXTURE_MODEL "TextureModel"

#define MOVE_SPEED 25.0f
#define ROTATE_SPEED 100.0f

#define RAY_DIST_LIMIT 10.0f

#define BALL_SHATTERING_MAX_DELAY 1.0f

using namespace bobcat;

DemoApp::DemoApp() {
	mode = 0;
	renderMode = 0;
	ballIndex = 0;
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
	resourceManager->loadTexture("kitteh.png", "Cat");
	resourceManager->loadTexture("Moon.png", "Moon");
	Texture* tex = resourceManager->getTexture("Cat");
	Texture* planeTex = resourceManager->getTexture("Moon");

	/*Setting up Scene*/
	sceneManager->addScene(new Scene());
	scene = sceneManager->getScene(0);
	scene->setRenderer(renderer);

	/*Adding meshes*/
	resourceManager->addMesh("Sphere.ply", "Sphere");
	resourceManager->addMesh("Monkey.ply", "Monkey");
	resourceManager->addMesh("Plane.ply", "Plane");
	resourceManager->addMesh("Cube.ply", "Cube");
	resourceManager->addMesh("Teapot.ply", "Teapot");

	/*Adding Materials*/
	mat = new Material();
	mat->color = glm::vec4(1.0, 1.0, 1.0, 1.0);
	mat->shader = shaderManager->getShader(TEXTURE_MODEL);
	mat->texture = tex;
	moonMat = new Material();
	moonMat->color = glm::vec4(1.0, 1.0, 1.0, 1.0);
	moonMat->shader = shaderManager->getShader(TEXTURE_MODEL);
	moonMat->texture = planeTex;
	noTexMat = new Material();
	noTexMat->color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	noTexMat->shader = shaderManager->getShader("JakeShader");

	//Initalize the objects, plugging the meshes into them
	GameObjectConstructionInfo cubeObjInfo;
	cubeObjInfo.setTransformValues(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.5f));
	cubeObjInfo.setColliderMode(ColliderMode::SPHERE);
	cubeObjInfo.setRigidbodyValues(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	cubeObjInfo.setMesh(resourceManager->getMesh("Teapot"));
	cubeObj = GameObjectCreator::ConstructFrom(cubeObjInfo);
	cubeObj->renderer->material = moonMat;

	/*std::vector<glm::vec3> cubeObjNorms = cubeObj->renderer->meshFilter->mesh->normals;
	for (size_t i = 0; i < cubeObjNorms.size(); i++) {
		cubeObjNorms[i].x = -0.7f;
		cubeObjNorms[i].y = 0.8f;
	}
	cubeObj->renderer->meshFilter->mesh->normals = cubeObjNorms;*/

	std::vector<glm::vec2> cubeObjUVs = cubeObj->renderer->meshFilter->mesh->uv;
	for (size_t i = 0; i < cubeObjUVs.size(); i++) {
		cubeObjUVs[i].x = 0.0f + (i * 0.0005f);
		cubeObjUVs[i].y = 0.0f + (i * 0.0005f);
	}
	cubeObj->renderer->meshFilter->mesh->uv = cubeObjUVs;

	/*cubeObjColor = cubeObj->renderer->meshFilter->mesh->color;
	for (size_t i = 0; i < cubeObjColor.size(); i++) {
		cubeObjColor[i].x = 0.0f;
		cubeObjColor[i].y = 0.0f + (i * 0.0005f);
		cubeObjColor[i].z = 0.0f + (i * 0.0005f);
	}
	cubeObj->renderer->meshFilter->mesh->color = cubeObjColor;*/
	
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
	planeObj->renderer->material = moonMat;
	scene->addGameObject(planeObj);

	logManager->writeLog(LogLevel::LOG_NONE, "This is a test log");
	logManager->writeLog(LogLevel::LOG_INFO, "This is a test log also");
	logManager->writeLog(LogLevel::LOG_ERROR, "This is an error!");

	GameObjectConstructionInfo cameraObjInfo;
	cameraObjInfo.setTransformValues(glm::vec3(0, 0, 20), glm::vec3(0.0f), glm::vec3(1.0f));
	//cameraObjInfo.setRigidbodyValues(glm::vec3(0), glm::vec3(0.0f, 35.0f, 0.0f), 0.0f);
	cameraObj = GameObjectCreator::ConstructFrom(cameraObjInfo);
	mainCamera = cameraObj->AddComponent<Camera>();
	scene->addGameObject(cameraObj);

	GameObjectConstructionInfo cameraObjChildInfo;
	cameraObjChildInfo.setTransformValues(glm::vec3(0, 0, 40), glm::vec3(0.0f), glm::vec3(1.0f));
	//cameraObjInfo.setRigidbodyValues(glm::vec3(0), glm::vec3(0.0f, 35.0f, 0.0f), 0.0f);
	cameraChildObj = GameObjectCreator::ConstructFrom(cameraObjChildInfo);
	cameraChildObj->AddComponent<Camera>();
	//cameraChildObj->AddComponent<TestDisplayPosition>();
	cameraObj->attachGameObject(cameraChildObj);

	origCameraPos = cameraObj->transform->position;

	lightSource = glm::vec3(0.0, -10.0, -1000.0);

	ray = new Ray(mainCamera->gameObject->transform->position, mainCamera->gameObject->transform->forward);

	renderer->setDebugRender(debugRenderOn);
}

void DemoApp::OnKeyEvent(){
	Engine::OnKeyEvent();
	if (inputSystem->getInputState(InputEnums::KeyCode::KEY_ESCAPE) == InputEnums::InputState::INPUT_PRESSED){
		Quit();
	} else if (inputSystem->getInputState(InputEnums::KeyCode::KEY_1) == InputEnums::InputState::INPUT_PRESSED){
		mode = 0;
	} else if (inputSystem->getInputState(InputEnums::KeyCode::KEY_2) == InputEnums::InputState::INPUT_PRESSED){
		mode = 1;
	} else if (inputSystem->getInputState(InputEnums::KeyCode::KEY_3) == InputEnums::InputState::INPUT_PRESSED) {
		mainCamera = cameraChildObj->GetComponent<Camera>();
	} else if (inputSystem->getInputState(InputEnums::KeyCode::KEY_4) == InputEnums::InputState::INPUT_PRESSED) {
		mainCamera = cameraObj->GetComponent<Camera>();
	} else if (inputSystem->getInputState(InputEnums::KeyCode::KEY_U) == InputEnums::InputState::INPUT_PRESSED){
		debugRenderOn = !debugRenderOn;
		renderer->setDebugRender(debugRenderOn);
	} else if (inputSystem->getInputState(InputEnums::KeyCode::KEY_Y) == InputEnums::InputState::INPUT_PRESSED){
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
	} else if (inputSystem->getInputState(InputEnums::KeyCode::KEY_C) == InputEnums::InputState::INPUT_PRESSED){
		cameraObj->RemoveComponent<TestDisplayPosition>();
	}
}

void DemoApp::InputUpdate(){
	if (inputSystem == nullptr) return;
	Engine::InputUpdate();
	switch (mode){
	case 0:
		//Camera Controls
		if (inputSystem->getInputState(InputEnums::KeyCode::KEY_UP) == InputEnums::InputState::INPUT_PRESSED){
			mainCamera->gameObject->transform->position += -MOVE_SPEED * mainCamera->gameObject->transform->forward * deltaTime;
		}
		if (inputSystem->getInputState(InputEnums::KeyCode::KEY_DOWN) == InputEnums::InputState::INPUT_PRESSED){
			mainCamera->gameObject->transform->position += MOVE_SPEED * mainCamera->gameObject->transform->forward * deltaTime;
		}
		if (inputSystem->getInputState(InputEnums::KeyCode::KEY_LEFT) == InputEnums::InputState::INPUT_PRESSED){
			mainCamera->gameObject->transform->position += -MOVE_SPEED * mainCamera->gameObject->transform->right * deltaTime;
		}
		if (inputSystem->getInputState(InputEnums::KeyCode::KEY_RIGHT) == InputEnums::InputState::INPUT_PRESSED){
			mainCamera->gameObject->transform->position += MOVE_SPEED * mainCamera->gameObject->transform->right * deltaTime;
		}
		if (inputSystem->getInputState(InputEnums::KeyCode::KEY_A) == InputEnums::InputState::INPUT_PRESSED){
			mainCamera->gameObject->transform->Rotate(ROTATE_SPEED * mainCamera->gameObject->transform->up * deltaTime);
		}
		if (inputSystem->getInputState(InputEnums::KeyCode::KEY_D) == InputEnums::InputState::INPUT_PRESSED){
			mainCamera->gameObject->transform->Rotate(-ROTATE_SPEED * mainCamera->gameObject->transform->up * deltaTime);
		}
		if (inputSystem->getInputState(InputEnums::KeyCode::KEY_W) == InputEnums::InputState::INPUT_PRESSED){
			mainCamera->gameObject->transform->Rotate(ROTATE_SPEED * glm::normalize(glm::abs(mainCamera->gameObject->transform->right)) * deltaTime);
		}
		if (inputSystem->getInputState(InputEnums::KeyCode::KEY_S) == InputEnums::InputState::INPUT_PRESSED){
			mainCamera->gameObject->transform->Rotate(-ROTATE_SPEED * glm::normalize(glm::abs(mainCamera->gameObject->transform->right)) * deltaTime);
		}
		if (inputSystem->getInputState(InputEnums::KeyCode::KEY_R) == InputEnums::InputState::INPUT_PRESSED){
			mainCamera->gameObject->transform->position = origCameraPos;
			mainCamera->gameObject->transform->ResetOrientation();
			mainCamera = cameraObj->GetComponent<Camera>();
		}
		break;
	case 1:
		//Sphere Controls
		if (inputSystem->getInputState(InputEnums::KeyCode::KEY_UP) == InputEnums::InputState::INPUT_PRESSED){
			cubeObj->transform->position += glm::vec3(0.0f, MOVE_SPEED, 0.0f) * deltaTime;
		}
		if (inputSystem->getInputState(InputEnums::KeyCode::KEY_DOWN) == InputEnums::InputState::INPUT_PRESSED){
			cubeObj->transform->position += glm::vec3(0.0f, -MOVE_SPEED, 0.0f) * deltaTime;
		}
		if (inputSystem->getInputState(InputEnums::KeyCode::KEY_LEFT) == InputEnums::InputState::INPUT_PRESSED){
			cubeObj->transform->position += glm::vec3(-MOVE_SPEED, 0.0f, 0.0f) * deltaTime;
		}
		if (inputSystem->getInputState(InputEnums::KeyCode::KEY_RIGHT) == InputEnums::InputState::INPUT_PRESSED){
			cubeObj->transform->position += glm::vec3(MOVE_SPEED, 0.0f, 0.0f) * deltaTime;
		} 
		if (inputSystem->getInputState(InputEnums::KeyCode::KEY_A) == InputEnums::InputState::INPUT_PRESSED){
			cubeObj->transform->Rotate(glm::vec3(0.0f, -ROTATE_SPEED, 0.0f) * deltaTime);
		}
		if (inputSystem->getInputState(InputEnums::KeyCode::KEY_D) == InputEnums::InputState::INPUT_PRESSED){
			cubeObj->transform->Rotate(glm::vec3(0.0f, ROTATE_SPEED, 0.0f) * deltaTime);
		}
		if (inputSystem->getInputState(InputEnums::KeyCode::KEY_W) == InputEnums::InputState::INPUT_PRESSED){
			cubeObj->transform->Rotate(glm::vec3(ROTATE_SPEED, 0.0f, 0.0f) * deltaTime);
		}
		if (inputSystem->getInputState(InputEnums::KeyCode::KEY_S) == InputEnums::InputState::INPUT_PRESSED){
			cubeObj->transform->Rotate(glm::vec3(-ROTATE_SPEED, 0.0f, 0.0f) * deltaTime);
		}
		if (inputSystem->getInputState(InputEnums::KeyCode::KEY_Q) == InputEnums::InputState::INPUT_PRESSED){
			cubeObj->transform->Rotate(glm::vec3(0.0f, 0.0f, ROTATE_SPEED) * deltaTime);
		}
		if (inputSystem->getInputState(InputEnums::KeyCode::KEY_E) == InputEnums::InputState::INPUT_PRESSED){
			cubeObj->transform->Rotate(glm::vec3(0.0f, 0.0f, -ROTATE_SPEED) * deltaTime);
		}
		if (inputSystem->getInputState(InputEnums::KeyCode::KEY_R) == InputEnums::InputState::INPUT_PRESSED){
			cubeObj->transform->position = sphereOrigPos;
			cubeObj->transform->ResetOrientation();
		}
		break;
	}
}

void DemoApp::Update(){
	Engine::Update();
	scene->updateGameObjects(deltaTime);
	ray->updateRay(mainCamera->gameObject->transform->position, mainCamera->gameObject->transform->forward);
	float dist;
	Collider* col = cubeObj->collider;
	if (ray->intersects(col->position, col->radius * col->scale, &dist) && (RAY_DIST_LIMIT == 0.0f ^ dist <= RAY_DIST_LIMIT)){
		//Something will happen here
		printf("Hit! at dist %f", dist);
	}else{
		//Something else will happen here
	}
	
	/*if (ballShatteringTime >= BALL_SHATTERING_MAX_DELAY) {
		std::vector<glm::vec3> cubeObjPos = cubeObj->renderer->meshFilter->mesh->positions;
		cubeObjPos[ballIndex] = glm::vec3(0.0f, 0.0f, 0.0f);
		cubeObj->renderer->meshFilter->mesh->positions = cubeObjPos;
		ballShatteringTime = 0.0f;
		ballIndex++;
		if (ballIndex >= cubeObjPos.size()) {
			ballIndex = 0;
		}
	} else {
		ballShatteringTime += deltaTime;
	}*/
	
	if (shaderManager->getCurrShader() != nullptr){
		glUniform3fv(shaderManager->getCurrShader()->lightingLoc, 1, glm::value_ptr(lightSource));
	}
}

void DemoApp::Draw(){
	Engine::Draw();
	scene->renderGameObjects();
}

void DemoApp::Quit(){
	printf("Quit");
	isGameRunning = false;
}