#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Mesh.h"
#include "Rect.h"
#include "TextureLoader.h"

class GameObject {
private:
	GameObject* parent;
	std::vector<GameObject*> children;
	std::string name;
	Mesh* mesh;
	Texture* tex;
	std::vector<GLfloat> uvCords;
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 force;
	glm::vec3 rotation;
	glm::vec3 scale;
	float friction;
	Rect3D collisionRect;
	GLuint modelLoc;
	std::vector<GLenum> drawModeVec;
	std::vector<int> indiceCountData;
	Shader* shader;
public:
	GameObject();

	~GameObject();

	std::vector<GameObject*> getChildren();

	std::string getName();

	glm::mat4 getModelMat();

	glm::vec3 getPosition();

	glm::vec3 getVelocity();

	glm::vec3 getRotation();

	Rect3D getCollisionRect();

	Mesh* getMesh();

	Shader* getShader();

	void setName(std::string _name);

	void setMesh(Mesh* _mesh);

	void setCollisionRect(Rect3D _rect);

	void setPosition(float _x, float _y, float _z);

	void setPosition(glm::vec3 _pos);

	void setVelocity(float _x, float _y, float _z);

	void setFriction(float _fric);

	void setRotationEuler(float _x, float _y, float _z);

	void setScale(float _x, float _y, float _z);

	void setShader(Shader* _shader);

	void setTexture(Texture* _tex, std::vector<GLfloat> _uvCords);

	void attachGameObject(GameObject* _gameObject);

	void UpdateDrawModes();

	void Update(float _gameTime);

	void Draw();
};

