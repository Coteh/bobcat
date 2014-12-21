#pragma once
#include <glm\glm.hpp>
#include "Transform.h"
#include "Collider.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

struct GameObjectConstructionInfo {
	friend class GameObject;
private:
	Transform* transform;
	Collider* collider;
	Mesh* mesh;
	Shader* shader;
	Texture* texture;
public:
	GameObjectConstructionInfo(){
		transform = nullptr;
		collider = nullptr;
		mesh = nullptr;
		shader = nullptr;
		texture = nullptr;
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

	inline void setMesh(Mesh* _mesh){
		mesh = _mesh;
	}

	inline void setShader(Shader* _shader){
		shader = _shader;
	}

	inline void setTexture(Texture* _texture){
		texture = _texture;
	}

	~GameObjectConstructionInfo(){
	}
};