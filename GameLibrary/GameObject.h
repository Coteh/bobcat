#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Mesh.h"
#include "Collider.h"
#include "TextureLoader.h"
#include "Transform.h"
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
	glm::vec3 velocity;
	glm::vec3 force;
	glm::vec3 rotationalVel; //torque
	glm::vec4 color;
	float friction;
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

	glm::vec3 getVelocity();

	glm::vec3 getRotationalVel();

	glm::vec4 getColor();

	Transform* getTransform();

	Collider* getCollider();

	MeshRenderer* getMeshRenderer();

	Shader* getShader();

	Texture* getTexture();

	void setName(std::string _name);

	void setMesh(Mesh* _mesh);

	void setTransform(Transform* _transform);

	void setCollider(Collider* _collider);

	void setVelocity(float _x, float _y, float _z);

	void setVelocity(glm::vec3 _vel);

	void setFriction(float _fric);

	void setRotationalVel(float _x, float _y, float _z);

	void setRotationalVel(glm::vec3 _rotVel);

	void setColor(glm::vec4 _color);

	void setShader(Shader* _shader);

	void setTexture(Texture* _tex);

	void attachGameObject(GameObject* _gameObject);

	void Update(float _deltaTime);

	void Draw();

	bool isWireFrameOn;
};

