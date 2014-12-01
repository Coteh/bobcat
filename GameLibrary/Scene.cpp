#include "Scene.h"


Scene::Scene() {
}

Scene::~Scene() {
	objectList.clear();
	std::vector<GameObject*> clearVec;
	clearVec.swap(objectList);
}

void Scene::setRenderer(Renderer* _renderer){
	renderer = _renderer;
}

void Scene::addGameObject(GameObject* _gameObject){
	objectList.push_back(_gameObject);
}

GameObject* Scene::getGameObject(std::string _name){
	for (size_t i = 0; i < objectList.size(); i++){
		if (objectList[i]->getName() == _name){
			return objectList[i];
		}
	}
	return NULL;
}

void Scene::updateGameObjects(float _deltaTime){
	for (size_t i = 0; i < objectList.size(); i++){
		objectList[i]->Update(_deltaTime);
	}
}

void Scene::renderGameObjects(){
	for (size_t i = 0; i < objectList.size(); i++){
		renderer->RenderObject(objectList[i]);
	}
}