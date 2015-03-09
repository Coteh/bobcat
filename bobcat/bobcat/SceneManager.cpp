#include "SceneManager.h"

using namespace bobcat;

static SceneManager* instance;

SceneManager::SceneManager() {
}


SceneManager::~SceneManager() {
	sceneVec.clear();
	std::vector<Scene*> clearVec;
	clearVec.swap(sceneVec);
}

SceneManager* SceneManager::getInstance(){
	if (instance == NULL){
		instance = new SceneManager();
	}
	return instance;
}

Scene* SceneManager::getScene(int _sceneIndex){
	return sceneVec[_sceneIndex];
}

void SceneManager::addScene(Scene* _scene){
	sceneVec.push_back(_scene);
}