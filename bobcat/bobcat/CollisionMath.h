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
		*/
		static bool CheckForCollision(Collider* _c1, Collider* _c2);

		static bool CheckForSphereToSphereCollision(SphereCollider* _sc1, SphereCollider* _sc2);

		static bool CheckForAABBToAABBCollision(BoxCollider* _bc1, BoxCollider* _bc2);

		static bool CheckForAABBToSphereCollision(BoxCollider* _bc, SphereCollider* _sc);

		static glm::vec3 ReflectVector(glm::vec3 _v, glm::vec3 _n);
	};

}