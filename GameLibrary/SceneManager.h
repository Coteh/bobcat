#pragma once
#include <vector>
#include "Scene.h"
class SceneManager {
private:
	static SceneManager* instane;
	std::vector<Scene*> sceneVec;
	SceneManager();
public:
	static SceneManager* getInstance();
	Scene* getScene(int _sceneIndex);
	void addScene(Scene* _scene);
	virtual ~SceneManager();
};

