#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Mesh.h"
#include "Collider.h"
#include "TextureLoader.h"

class GameObject {
private:
	GameObject* parent;
	std::vector<GameObject*> children;
	std::string name;
	Mesh* mesh;
	Texture* tex;
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 force;
	glm::vec3 rotation;
	glm::vec3 rotationalVel; //torque
	glm::vec3 scale;
	glm::mat4 additionalMats;
	float friction;
	Collider* collider;
	std::vector<GLenum> drawModeVec;
	std::vector<int> indiceCountData;
	Shader* shader;
	bool isRendering;
public:
	GameObject();

	~GameObject();

	std::vector<GameObject*> getChildren();

	std::string getName();

	glm::mat4 getModelMat();

	glm::vec3 getPosition();

	glm::vec3 getVelocity();

	glm::vec3 getRotation();

	glm::vec3 getRotationalVel();

	glm::vec3 getScale();

	Collider* getCollider();

	Mesh* getMesh();

	Shader* getShader();

	Texture* getTexture();

	void setName(std::string _name);

	void setMesh(Mesh* _mesh);

	void setCollider(Collider* _collider);

	void setPosition(float _x, float _y, float _z);

	void setPosition(glm::vec3 _pos);

	void setVelocity(float _x, float _y, float _z);

	void setVelocity(glm::vec3 _vel);

	void setFriction(float _fric);

	void setRotationEuler(float _x, float _y, float _z);

	void setRotationEuler(glm::vec3 _rotEuler);

	void setRotationalVel(float _x, float _y, float _z);

	void setRotationalVel(glm::vec3 _rotVel);

	void setScale(float _x, float _y, float _z);

	void setScale(glm::vec3 _scale);

	void setShader(Shader* _shader);

	void setTexture(Texture* _tex);

	void setIsRending(bool _expression);

	void attachGameObject(GameObject* _gameObject);

	void addMatrixTransformation(glm::mat4 _mat);

	void Update(float _deltaTime);

	void Draw();

	bool isWireFrameOn;
};

