#include "GameObjectCreator.h"
#include "GameObject.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Rigidbody.h"

using namespace bobcat;

GameObject* GameObjectCreator::ConstructFrom(GameObjectConstructionInfo _info){
	GameObject* go = new GameObject();
	if (_info.isTransformSet){
		Transform* transform = go->AddComponent<Transform>();
		transform->position = _info.position;
		transform->Rotate(_info.rotation);
		transform->scale = _info.scale;
		go->transform = transform;
	}
	if (_info.colliderType > 0){
		Collider* collider;
		switch (_info.colliderType){
		case ColliderType::BOX:
			collider = go->AddComponent<BoxCollider>();
			break;
		case ColliderType::SPHERE:
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
	if (_info.isRigidbodySet){
		Rigidbody* rigidBody = go->AddComponent<Rigidbody>();
		rigidBody->velocity = _info.velocity;
		rigidBody->rotationalVel = _info.rotationalVel;
		rigidBody->friction = _info.friction;
		go->rigidbody = rigidBody;
	}
	if (_info.mesh != nullptr){
		go->renderer = go->AddComponent<MeshRenderer>();
		MeshFilter* meshFilter = go->AddComponent<MeshFilter>();
		meshFilter->mesh = _info.mesh;
		go->renderer->meshFilter = meshFilter;
		go->renderer->isEnabled = true;
	}
	return go;
}