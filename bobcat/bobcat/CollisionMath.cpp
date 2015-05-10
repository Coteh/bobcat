#include "CollisionMath.h"
#include "GameObject.h"

using namespace bobcat;

bool CollisionMath::CheckForCollision(Collider* _c1, Collider* _c2){
	if (_c1->colliderType == ColliderType::SPHERE){
		if (_c2->colliderType == ColliderType::SPHERE){
			return CheckForSphereToSphereCollision((SphereCollider*)_c1, (SphereCollider*)_c2);
		} else if (_c2->colliderType == ColliderType::BOX){
			return CheckForAABBToSphereCollision((BoxCollider*)_c2, (SphereCollider*)_c1);
		}
	} else if (_c1->colliderType == ColliderType::BOX){
		if (_c2->colliderType == ColliderType::BOX){
			return CheckForAABBToAABBCollision((BoxCollider*)_c1, (BoxCollider*)_c2);
		} else if (_c2->colliderType == ColliderType::SPHERE){
			return CheckForAABBToSphereCollision((BoxCollider*)_c1, (SphereCollider*)_c2);
		}
	}
	return false; //not implemented yet
}

bool CollisionMath::CheckForSphereToSphereCollision(SphereCollider* _sc1, SphereCollider* _sc2){
	float distance = glm::distance(_sc1->gameObject->transform->position, _sc2->gameObject->transform->position);

	//If the distance between the two spheres is less than or equal to the sum of both radii, then there is a collision
	return (distance <= _sc1->radius * _sc1->gameObject->transform->scale.x + _sc2->radius * _sc2->gameObject->transform->scale.x);
}

bool CollisionMath::CheckForAABBToAABBCollision(BoxCollider* _bc1, BoxCollider* _bc2){
	Transform* bc1Trans = _bc1->gameObject->transform;
	Transform* bc2Trans = _bc2->gameObject->transform;
	if (::abs(bc1Trans->position.x - bc2Trans->position.x) > (_bc1->width * bc1Trans->scale.x + _bc2->width * bc2Trans->scale.x)) return false;
	if (::abs(bc1Trans->position.y - bc2Trans->position.y) > (_bc1->height * bc1Trans->scale.y + _bc2->height * bc2Trans->scale.y)) return false;
	if (::abs(bc1Trans->position.z - bc2Trans->position.z) > (_bc1->length * bc1Trans->scale.z + _bc2->length * bc2Trans->scale.z)) return false;
	return true; //collision detected!
}

bool CollisionMath::CheckForAABBToSphereCollision(BoxCollider* _bc, SphereCollider* _sc){
	//Get the opposing corners of the cube
	glm::vec3 boxPos = _bc->gameObject->transform->position;
	glm::vec3 spherePos = _sc->gameObject->transform->position;
	glm::vec3 boxScale = _bc->gameObject->transform->scale;
	glm::vec3 corner1 = glm::vec3(boxPos.x - (_bc->width * boxScale.x) / 2, boxPos.y - (_bc->height * boxScale.y) / 2, boxPos.z - (_bc->length * boxScale.z) / 2);
	glm::vec3 corner2 = glm::vec3(boxPos.x + (_bc->width * boxScale.x) / 2, boxPos.y + (_bc->height * boxScale.y) / 2, boxPos.z + (_bc->length * boxScale.z) / 2);
	
	//Find the square of the distance from the sphere to the box
	float radius = (_sc->radius * _sc->gameObject->transform->scale.x);
	float distanceSquared = ::pow(radius, 2);

	if (spherePos.x < corner1.x){
		distanceSquared -= ::pow(spherePos.x - corner1.x, 2);
	} else if (spherePos.x > corner2.x){
		distanceSquared -= ::pow(spherePos.x - corner2.x, 2);
	}
	if (spherePos.y < corner1.y){
		distanceSquared -= ::pow(spherePos.y - corner1.y, 2);
	} else if (spherePos.y > corner2.y){
		distanceSquared -= ::pow(spherePos.y - corner2.y, 2);
	}
	if (spherePos.z < corner1.z){
		distanceSquared -= ::pow(spherePos.z - corner1.z, 2);
	} else if (spherePos.z > corner2.z){
		distanceSquared -= ::pow(spherePos.z - corner2.z, 2);
	}
	return (distanceSquared > 0);
}

glm::vec3 CollisionMath::ReflectVector(glm::vec3 _v, glm::vec3 _n){
	//Save vector length for later
	float vLength = glm::length(_v);

	//Normalize the vectors
	glm::vec3 v = glm::normalize(_v);
	glm::vec3 n = glm::normalize(_n);

	//r is the output vector
	glm::vec3 r = v;

	//Use the dot product to figure out the "reflected" vector
	r = -2 * glm::dot(v, n) * n + v;

	//Restore length to reflected vector
	r *= vLength;

	//Return the reflected vector
	return r;
}