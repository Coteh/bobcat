#pragma once
#include <vector>
#include "Renderer.h"
#include "GameObject.h"

class Scene
{
private:
	std::vector<GameObject> objectList;
	Renderer* renderer;
public:
	Scene();
	~Scene();
	void setRenderer(Renderer* _renderer);
	void addGameObject(GameObject* _gameObject);
	GameObject* getGameObject(std::string _name);
	void updateGameObjects(float _gameTime);
	void renderGameObjects();
};

