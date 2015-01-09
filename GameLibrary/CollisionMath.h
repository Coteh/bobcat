#pragma once
#include "SphereCollider.h"
#include "BoxCollider.h"

namespace bobcat {

	/**
	* Class containing static methods related to collision calculations.
	*/
	class CollisionMath {
	public:
		/**
		* Check for a collision between two colliders.
		* @param _c1 First collider.
		* @param _c2 Second collider.
		* @note This method has not been implemented yet. Do not use.
		*/
		static bool CheckForCollision(Collider* _c1, Collider* _c2);
	};

}