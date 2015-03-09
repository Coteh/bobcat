#pragma once
#include "GameObjectConstructionInfo.h"

namespace bobcat {

	class GameObject;

	/**
	* Helper functions for creating GameObjects.
	*/
	class GameObjectCreator {
	public:
		/**
		* Construct a GameObject from predefined info.
		* @param _info GameObjectConstructionInfo instance containing info to apply to a new GameObject.
		*/
		static GameObject* ConstructFrom(GameObjectConstructionInfo _info);
	};

}