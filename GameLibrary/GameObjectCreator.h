#pragma once
#include "GameObjectConstructionInfo.h"

class GameObject;

class GameObjectCreator {
public:
	static GameObject* ConstructFrom(GameObjectConstructionInfo _info);
};

