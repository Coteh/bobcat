#pragma once
#include <glm\glm.hpp>
#include "Transform.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "Mesh.h"

struct GameObjectConstructionInfo {
	friend class GameObject;
private:
	Transform* transform;
	Collider* collider;
	Rigidbody* rigidbody;
	Mesh* mesh;
public:
	GameObjectConstructionInfo(){
		transform = nullptr;
		collider = nullptr;
		rigidbody = nullptr;
		mesh = nullptr;
	}

	inline void setTransformValues(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scl){
		transform = new Transform();
		transform->position = _pos;
		transform->rotation = _rot;
		transform->scale = _scl;
	}

	inline void setTransformValues(){
		setTransformValues(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
	}

	inline void setCollider(Collider* _col){
		collider = _col;
		collider->setScale(1.0f);
		collider->setDimensions(1.0f, 1.0f, 1.0f);
	}

	inline void setRigidbodyValues(glm::vec3 _velocity, glm::vec3 _rotationalVel, float _friction){
		rigidbody = new Rigidbody();
		rigidbody->velocity = _velocity;
		rigidbody->rotationalVel = _rotationalVel;
		rigidbody->friction = _friction;
	}

	inline void setRigidbodyValues(){
		setRigidbodyValues(glm::vec3(0.0f), glm::vec3(0.0f), 1.0f);
	}

	inline void setMesh(Mesh* _mesh){
		mesh = _mesh;
	}

	~GameObjectConstructionInfo(){
	}
};