#pragma once
#include <vector>
#include "AbstractRenderSystem.h"
#include "GameObject.h"

class Scene
{
private:
	std::vector<GameObject*> objectList;
	AbstractRenderSystem* renderer;
public:
	Scene();
	virtual ~Scene();
	void setRenderer(AbstractRenderSystem* _renderer);
	void addGameObject(GameObject* _gameObject);
	GameObject* getGameObject(std::string _name);
	void updateGameObjects(float _deltaTime);
	void renderGameObjects();
};

