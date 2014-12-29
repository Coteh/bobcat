#include "GameObjectCreator.h"
#include "GameObject.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Rigidbody.h"

GameObject* GameObjectCreator::ConstructFrom(GameObjectConstructionInfo _info){
	GameObject* go = new GameObject();
	Transform* transform = go->AddComponent<Transform>();
	transform->position = _info.position;
	transform->rotation = _info.rotation;
	transform->scale = _info.scale;
	go->transform = transform;
	if (_info.colliderMode > 0){
		Collider* collider;
		switch (_info.colliderMode){
		case ColliderMode::BOX:
			collider = go->AddComponent<BoxCollider>();
			break;
		case ColliderMode::SPHERE:
			collider = go->AddComponent<SphereCollider>();
			break;
		default:
			collider = go->AddComponent<Collider>();
			break;
		}
		collider->setScale(1.0f);
		collider->setDimensions(1.0f, 1.0f, 1.0f);
		go->collider = collider;
	}
	Rigidbody* rigidBody = go->AddComponent<Rigidbody>();
	rigidBody->velocity = _info.velocity;
	rigidBody->rotationalVel = _info.rotationalVel;
	rigidBody->friction = _info.friction;
	go->rigidbody = rigidBody;
	go->setMesh(_info.mesh);
	return go;
}