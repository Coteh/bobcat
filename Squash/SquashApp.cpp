#include "SquashApp.h"


SquashApp::SquashApp() {
	
}


SquashApp::~SquashApp() {
}

void SquashApp::Init(){
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

	shaderManager->addShader(ShaderLoader::LoadShaders(shaders), "TestShader");
	shaderManager->addShader(ShaderLoader::LoadShaders(shaders2), "TestShader2");

	/*Setting up Scene*/
	sceneManager->addScene(new Scene());
	scene = sceneManager->getScene(0);
	scene->setRenderer(renderer);

	/*Setting up meshes*/
	meshManager->addMesh("Paddle.ply", "Paddle");
	meshManager->addMesh("Circle.ply", "Circle");

	//Initalize the objects, plugging the meshes into them
	//Collision rectangles are faked for now
	playerOne = new GameObject();
	playerOne->setMesh(meshManager->getMesh("Paddle"));
	playerOne->setShader(shaderManager->getShader("TestShader"));
	playerOne->setPosition(-1.0f, -1.5f, 0);
	playerOne->setVelocity(0.0f, 0.0f, 0.0f);
	playerOne->setScale(0.5f, 0.35f, 0.35f);
	Rect3D p1Rect = Rect3D(playerOne->getPosition(), 1.0f, 0.35f, 0.35f);
	playerOne->setCollisionRect(p1Rect);
	scene->addGameObject(playerOne);

	playerTwo = new GameObject();
	playerTwo->setMesh(meshManager->getMesh("Paddle"));
	playerTwo->setShader(shaderManager->getShader("TestShader"));
	playerTwo->setPosition(1.0f, -1.5f, 0);
	playerTwo->setVelocity(0.0f, 0.0f, 0.0f);
	playerTwo->setScale(0.5f, 0.35f, 0.35f);
	Rect3D p2Rect = Rect3D(playerOne->getPosition(), 1.0f, 0.35f, 0.35f);
	playerTwo->setCollisionRect(p2Rect);
	scene->addGameObject(playerTwo);

	ballObj = new GameObject();
	ballObj->setMesh(meshManager->getMesh("Circle"));
	ballObj->setShader(shaderManager->getShader("TestShader"));
	ballObj->setPosition(0, 0.0f, 0);
	ballObj->setVelocity(0.0f, 0.0f, 0.0f);
	ballObj->setScale(0.25f, 0.25f, 0.25f);
	Rect3D ballRect = Rect3D(playerOne->getPosition(), 5.0f, 5.0f, 5.0f);
	ballObj->setCollisionRect(ballRect);
	ballVelChange = glm::vec3(0.01f, -0.03f, 0.0);
	scene->addGameObject(ballObj);

	ballHitter = 0.0f; score1 = score2 = 0.0f;
}

void SquashApp::OnKeyEvent(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods){
	Engine::OnKeyEvent(_window, _key, _scancode, _action, _mods);
	if (_action == GLFW_PRESS){
		if (_key == GLFW_KEY_ESCAPE){
			printf("Quit");
			isGameRunning = false;
		}
	}
}

void SquashApp::OnKeyHandle(){
	Engine::OnKeyHandle();
	//Camera Controls
	if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_EQUAL) == GLFW_PRESS){
		camera->IncrementZoom(-2.0f * deltaTime);
	} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_MINUS) == GLFW_PRESS){
		camera->IncrementZoom(2.0f * deltaTime);
	}
	//Player One, Player Two, and Ball Controls
	glm::vec3 playerOnePos = playerOne->getPosition();
	glm::vec3 playerTwoPos = playerTwo->getPosition();
	glm::vec3 playerOneVelChange = glm::vec3(0.0f);
	glm::vec3 playerTwoVelChange = glm::vec3(0.0f);
	if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_LEFT) == GLFW_PRESS){
		playerOneVelChange += glm::vec3(-ballSpeed, 0.0, 0.0);
	} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_RIGHT) == GLFW_PRESS){
		playerOneVelChange += glm::vec3(ballSpeed, 0.0, 0.0);
	} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_A) == GLFW_PRESS){
		playerTwoVelChange += glm::vec3(-ballSpeed, 0.0, 0.0);
	} else if (glfwGetKey(currActiveWindowInstance, GLFW_KEY_D) == GLFW_PRESS){
		playerTwoVelChange += glm::vec3(ballSpeed, 0.0, 0.0);
	}
	/*Paddle collision checks*/
	if (playerOnePos.x + playerOneVelChange.x >= playerTwoPos.x - (playerTwo->getCollisionRect().width - 0.1)){
		playerOneVelChange.x = 0;
	}
	if (playerTwoPos.x + playerTwoVelChange.x <= playerOnePos.x + (playerOne->getCollisionRect().width - 0.1)){
		playerTwoVelChange.x = 0;
	}
	playerOne->setPosition(playerOnePos += (playerOneVelChange * deltaTime));
	playerTwo->setPosition(playerTwoPos += (playerTwoVelChange * deltaTime));
}

void SquashApp::Update(){
	Engine::Update();
	scene->updateGameObjects(deltaTime);
	/*Updating the ball*/
	glm::vec3 ballPos = ballObj->getPosition();
	//Ball collision checks
	if (ballPos.x > 1.6f){
		ballPos.x = 1.6f;
		ballVelChange.x = -ballVelChange.x;
	} else if (ballPos.x < -1.6f){
		ballPos.x = -1.6f;
		ballVelChange.x = -ballVelChange.x;
	}
	if (ballPos.y > 1.6f){
		ballPos.y = 1.6f;
		ballVelChange.y = -ballVelChange.y;
	} else if (ballPos.y < -2.6f){
		//Determining score
		if (ballHitter == 1){
			score1++; //goes to player 1
			printf("Player 1 is now at %d points!\n", score1);
		} else if (ballHitter == 2){
			score2++; //goes to player 2
			printf("Player 2 is now at %d points!\n", score2);
		} else{
			//no points awarded
			printf("It's a draw!\n");
		}
		ballHitter = 0; //resetting ball hitter
		ballSpeedMultiplier = 1.0f; //resetting ball speed
		//Resetting ball position
		ballPos = glm::vec3(0.0f, 0.0f, 0.0f);
	} else if (ballPos.y <= playerOne->getPosition().y + (playerOne->getCollisionRect().height / 2)
		&& ballPos.y >= playerOne->getPosition().y - (playerOne->getCollisionRect().height / 2)){
		Rect3D p1Rect = playerOne->getCollisionRect();
		Rect3D p2Rect = playerTwo->getCollisionRect();
		if (ballPos.x <= playerOne->getPosition().x + (p1Rect.width / 2) && ballPos.x >= playerOne->getPosition().x - (p1Rect.width / 2)){
			ballHitter = 1; //player 1 is hitting
			ballPos.y = playerOne->getPosition().y + (playerOne->getCollisionRect().height / 2);
			ballVelChange.y = -ballVelChange.y;
			ballSpeedMultiplier += 1.0f;
		} else if (ballPos.x <= playerTwo->getPosition().x + (p2Rect.width / 2) && ballPos.x >= playerTwo->getPosition().x - (p1Rect.width / 2)){
			ballHitter = 2; //player 2 is hitting
			ballPos.y = playerTwo->getPosition().y + (playerOne->getCollisionRect().height / 2);
			ballVelChange.y = -ballVelChange.y;
			ballSpeedMultiplier += 1.0f;
		}
	}
	ballObj->setPosition(ballPos += ((ballVelChange * ballSpeedMultiplier) * deltaTime));
	glm::vec3 rot = ballObj->getRotation();
	ballObj->setRotationEuler(rot.x + (0.0f * deltaTime), rot.y + (0.0f * deltaTime), rot.z + (10.0f * deltaTime));
}

void SquashApp::Draw(){
	Engine::Draw();
	scene->renderGameObjects();
}
