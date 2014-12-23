#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Mesh.h"
#include "Collider.h"
#include "TextureLoader.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "MeshRenderer.h"
#include "GameObjectConstructionInfo.h"

class GameObject {
private:
	GameObject* parent;
	std::vector<GameObject*> children;
	std::string name;
	Mesh* mesh;
	Texture* tex;
	Transform* transform;
	Rigidbody* rigidbody;
	Collider* collider;
	Shader* shader;
	MeshRenderer* meshRenderer;
public:
	GameObject();

	GameObject(GameObjectConstructionInfo* _constructionInfo);

	~GameObject();

	std::vector<GameObject*> getChildren();

	std::string getName();

	glm::mat4 getModelMat();

	Transform* getTransform();

	Collider* getCollider();

	Rigidbody* getRigidbody();

	MeshRenderer* getMeshRenderer();

	Shader* getShader();

	Texture* getTexture();

	void setName(std::string _name);

	void setMesh(Mesh* _mesh);

	void setTransform(Transform* _transform);

	void setCollider(Collider* _collider);

	void setRigidbody(Rigidbody* _rigidbody);

	void setShader(Shader* _shader);

	void setTexture(Texture* _tex);

	void attachGameObject(GameObject* _gameObject);

	void Update(float _deltaTime);

	void Draw();

	bool isWireFrameOn;
};

