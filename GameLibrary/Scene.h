#pragma once
#include <vector>
#include "AbstractRenderer.h"
#include "GameObject.h"

class Scene
{
private:
	std::vector<GameObject*> objectList;
	AbstractRenderer* renderer;
public:
	Scene();
	virtual ~Scene();
	void setRenderer(AbstractRenderer* _renderer);
	void addGameObject(GameObject* _gameObject);
	GameObject* getGameObject(std::string _name);
	void updateGameObjects(float _deltaTime);
	void renderGameObjects();
};

