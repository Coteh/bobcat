#include "BobcatDemo.h"
#include "Components/ParticleSystem.h"
#include <glm\gtc\type_ptr.hpp>

#include <glm/gtc/noise.hpp>
#include <glm/gtc/random.hpp>

#define TEXTURE_MODEL "ScottTextureShader"

#define MOVE_SPEED 25.0f
#define ROTATE_SPEED 100.0f

#define RAY_DIST_LIMIT 10.0f

using namespace bobcat;

BobcatDemo::BobcatDemo() {
	mode = 0;
	renderMode = 0;
	ballIndex = 0;
}

BobcatDemo::BobcatDemo(int _engineCmd) : BobcatDemo(){
	if (_engineCmd){
		Init();
	}
}

BobcatDemo::~BobcatDemo() {
	delete ray;
	delete mat;
	delete noTexMat;
}

void BobcatDemo::Init(){
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

	ShaderLoadInfo shaders7[] = {
		{ GL_VERTEX_SHADER, "scottshader-vert.glsl" },
		{ GL_FRAGMENT_SHADER, "scottshader-frag.glsl" },
		{ GL_NONE, NULL }
	};

	ShaderLoadInfo shaders8[] = {
		{ GL_VERTEX_SHADER, "scotttextureshader-vert.glsl" },
		{ GL_FRAGMENT_SHADER, "scotttextureshader-frag.glsl" },
		{ GL_NONE, NULL }
	};

	ShaderLoadInfo shaders9[] = {
		{ GL_VERTEX_SHADER, "particle-vert.glsl" },
		{ GL_FRAGMENT_SHADER, "colormodel-frag.glsl" },
		{ GL_NONE, NULL }
	};

	ShaderLoadInfo shaders10[] = {
		{ GL_VERTEX_SHADER, "toon-vert.glsl" },
		{ GL_FRAGMENT_SHADER, "toon-frag.glsl" },
		{ GL_NONE, NULL }
	};

	shaderManager->addShader(ShaderLoader::LoadShaders(shaders), "TestShader");
	shaderManager->addShader(ShaderLoader::LoadShaders(shaders2), "TestShader2");
	shaderManager->addShader(ShaderLoader::LoadShaders(shaders3), "JakeShader");
	shaderManager->addShader(ShaderLoader::LoadShaders(shaders4), "ColorModel");
	shaderManager->addShader(ShaderLoader::LoadShaders(shaders5), "TextureModel");
	shaderManager->addShader(ShaderLoader::LoadShaders(shaders6), "UniformColor");
	shaderManager->addShader(ShaderLoader::LoadShaders(shaders7), "ScottShader");
	shaderManager->addShader(ShaderLoader::LoadShaders(shaders8), "ScottTextureShader");
	shaderManager->addShader(ShaderLoader::LoadShaders(shaders9), "ParticleShader");
	shaderManager->addShader(ShaderLoader::LoadShaders(shaders10), "ToonShader");

	/*Setting up Textures*/
	resourceManager->loadTexture("kitteh.png", "Cat");
	resourceManager->loadTexture("Grass.png", "Grass");
	Texture* tex = resourceManager->getTexture("Cat");
	Texture* planeTex = resourceManager->getTexture("Grass");

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
	noTexMat->shader = shaderManager->getShader("ColorModel");
	Material* toonMat = new Material();
	toonMat->color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	toonMat->shader = shaderManager->getShader("ToonShader");
	resourceManager->addMaterial(toonMat, "ToonMaterial");
	Material* toonMoonMat = new Material();
	toonMoonMat->color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	toonMoonMat->shader = shaderManager->getShader("ToonShader");
	resourceManager->addMaterial(toonMoonMat, "ToonMoonMaterial");

	//Initalize the objects, plugging the meshes into them
	GameObjectConstructionInfo cubeObjInfo;
	cubeObjInfo.setTransformValues(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.5f));
	cubeObjInfo.setColliderMode(ColliderMode::SPHERE);
	cubeObjInfo.setRigidbodyValues(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	cubeObjInfo.setMesh(resourceManager->getMesh("Teapot"));
	cubeObj = GameObjectCreator::ConstructFrom(cubeObjInfo);
	cubeObj->renderer->material = mat;

	sphereTorque = cubeObj->rigidbody->rotationalVel;
	scene->addGameObject(cubeObj);

	cubeObj = GameObjectCreator::ConstructFrom(cubeObjInfo);
	cubeObj->transform->position += glm::vec3(-5, 0, 0);
	cubeObj->transform->scale = glm::vec3(0.5f, 0.5f, 0.5f);
	cubeObj->renderer->material = moonMat;
	scene->addGameObject(cubeObj);

	//Create perlin noise for teapot model
	std::vector<glm::vec2> fiyaTex = cubeObj->renderer->meshFilter->mesh->uv;
	for (size_t i = 0; i < fiyaTex.size(); i++){
		float noised = glm::simplex(glm::circularRand<float>(1.0f));
		fiyaTex[i] = glm::vec2(noised, noised);
	}
	cubeObj->renderer->meshFilter->mesh->uv = fiyaTex;

	cubeObj->renderer->meshFilter->mesh = resourceManager->getMesh("Sphere");

	cubeObjInfo.setMesh(resourceManager->getMesh("Sphere"));
	GameObject* toonMoonObj = GameObjectCreator::ConstructFrom(cubeObjInfo);
	toonMoonObj->transform->position += glm::vec3(-10, 0, -100);
	toonMoonObj->transform->scale = glm::vec3(0.5f, 0.5f, 0.5f);
	toonMoonObj->renderer->material = toonMoonMat;
	scene->addGameObject(toonMoonObj);

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
	cameraObj->attachGameObject(cameraChildObj);

	origCameraPos = cameraObj->transform->position;

	lightSource = glm::vec3(0.0, -100.0, -100.0);

	ray = new Ray(mainCamera->gameObject->transform->position, mainCamera->gameObject->transform->forward);

	renderer->setDebugRender(debugRenderOn);
}

void BobcatDemo::OnKeyEvent(){
	Engine::OnKeyEvent();
	if (inputSystem->getInputState(InputEnums::KeyCode::KEY_ESCAPE) == InputEnums::InputState::INPUT_PRESSED){
		Quit();
	} else if (inputSystem->getInputState(InputEnums::KeyCode::KEY_NUM1) == InputEnums::InputState::INPUT_PRESSED){
		printf("This numpad works!");
	} else if (inputSystem->getInputState(InputEnums::KeyCode::KEY_1) == InputEnums::InputState::INPUT_PRESSED){
		mode = 0;
	} else if (inputSystem->getInputState(InputEnums::KeyCode::KEY_2) == InputEnums::InputState::INPUT_PRESSED){
		mode = 1;
	} else if (inputSystem->getInputState(InputEnums::KeyCode::KEY_3) == InputEnums::InputState::INPUT_PRESSED) {
		mainCamera = cameraChildObj->GetComponent<Camera>();
	} else if (inputSystem->getInputState(InputEnums::KeyCode::KEY_4) == InputEnums::InputState::INPUT_PRESSED) {
		mainCamera = cameraObj->GetComponent<Camera>();
	} else if (inputSystem->getInputState(InputEnums::KeyCode::KEY_5) == InputEnums::InputState::INPUT_PRESSED) {
		//Create perlin noise for teapot model
		std::vector<glm::vec2> fireTex = cubeObj->renderer->meshFilter->mesh->uv;
		for (size_t i = 0; i < fireTex.size(); i++){
			float noised = glm::simplex(glm::circularRand<float>(1.0f));
			fireTex[i] = glm::vec2(noised, noised);
		}
		cubeObj->renderer->meshFilter->mesh->uv = fireTex;
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
	}
}

void BobcatDemo::InputUpdate(){
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
	if (inputSystem->getInputState(InputEnums::KeyCode::KEY_SPACE) == InputEnums::InputState::INPUT_PRESSED){
		if (rayOnTopOfCube){
			cubeObj->AddComponent<ParticleSystem>();
		}
	}
}

void BobcatDemo::Update(){
	Engine::Update();
	scene->updateGameObjects(deltaTime);
	ray->updateRay(mainCamera->gameObject->transform->position, mainCamera->gameObject->transform->forward);
	float dist;
	Collider* col = cubeObj->collider;
	if (ray->intersects(col->position, col->radius * col->scale, &dist) && (RAY_DIST_LIMIT == 0.0f ^ dist <= RAY_DIST_LIMIT)){
		//Something will happen here
		rayOnTopOfCube = true;
		printf("Hit! at dist %f", dist);
	} else{
		//Something else will happen here
		rayOnTopOfCube = false;
	}

	if (shaderManager->getCurrShader() != nullptr){
		glUniform3fv(shaderManager->getCurrShader()->getShaderUniform("LightPos"), 1, glm::value_ptr(lightSource));
	}
}

void BobcatDemo::Draw(){
	Engine::Draw();
	scene->renderGameObjects();
}

void BobcatDemo::Quit(){
	printf("Quit");
	isGameRunning = false;
}