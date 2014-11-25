#pragma once
#include "SphereCollider.h"
#include "BoxCollider.h"

class CollisionMath {
public:
	static bool CheckForCollision(Collider* _c1, Collider* _c2);
};

