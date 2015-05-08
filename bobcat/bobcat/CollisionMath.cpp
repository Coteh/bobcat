#include "CollisionMath.h"
#include "GameObject.h"

using namespace bobcat;

bool CollisionMath::CheckForCollision(Collider* _c1, Collider* _c2){
	if (_c1->colliderType == ColliderType::SPHERE){
		if (_c2->colliderType == ColliderType::SPHERE){
			return CheckForSphereToSphereCollision((SphereCollider*)_c1, (SphereCollider*)_c2);
		}
	}
	return false; //not implemented yet
}

bool CollisionMath::CheckForSphereToSphereCollision(SphereCollider* _sc1, SphereCollider* _sc2){
	float distance = glm::distance(_sc1->gameObject->transform->position, _sc2->gameObject->transform->position);

	//If the distance between the two spheres is less than or equal to the sum of both radii, then there is a collision
	return (distance <= _sc1->radius * _sc1->gameObject->transform->scale.x + _sc2->radius * _sc2->gameObject->transform->scale.x);
}