#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Mesh.h"
#include "Rect.h"

class GameObject {
private:
	GameObject* parent;
	std::vector<GameObject*> children;
	std::string name;
	Mesh* mesh;
	GLuint tex;
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 force;
	glm::vec3 rotAxis;
	Rect3D collisionRect;
	float angle, torque;
	GLuint modelLoc;
	std::vector<GLenum> drawModeVec;
	std::vector<int> indiceCountData;
public:
	GameObject();
	~GameObject();
	std::string getName();
	glm::mat4 getModelMat();
	void setName(std::string _name);
	void setMesh(Mesh* _mesh);
	void setCollisionRect(Rect3D _rect);
	void setPosition(float _x, float _y, float _z);
	void setVelocity(float _x, float _y, float _z);
	void setTorque(float _torque);
	void setRotAxis(float _x, float _y, float _z);
	void attachGameObject(GameObject* _gameObject);
	void UpdateDrawModes();
	void Update(float _gameTime);
	void Draw(GLuint _modelLoc);
};

