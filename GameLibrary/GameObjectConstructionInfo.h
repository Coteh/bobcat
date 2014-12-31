#pragma once
#include <glm\glm.hpp>
#include "Mesh.h"

namespace ColliderMode{
	enum ColliderMode{
		NONE = 0,
		BOX = 1,
		SPHERE = 2
	};
}

struct GameObjectConstructionInfo {
	friend class GameObjectCreator;
private:
	bool isTransformSet = false;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	ColliderMode::ColliderMode colliderMode;

	bool isRigidbodySet = false;
	glm::vec3 velocity;
	glm::vec3 rotationalVel;
	float friction;

	Mesh* mesh;
public:
	GameObjectConstructionInfo(){
		mesh = nullptr;
	}

	inline void setTransformValues(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scl){
		position = _pos;
		rotation = _rot;
		scale = _scl;
		isTransformSet = true;
	}

	inline void setTransformValues(){
		setTransformValues(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
	}

	inline void setColliderMode(ColliderMode::ColliderMode _mode){
		colliderMode = _mode;
	}

	inline void setRigidbodyValues(glm::vec3 _velocity, glm::vec3 _rotationalVel, float _friction){
		velocity = _velocity;
		rotationalVel = _rotationalVel;
		friction = _friction;
		isRigidbodySet = true;
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