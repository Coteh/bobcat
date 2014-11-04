#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Mesh.h"

class GameObject {
private:
	std::string name;
	Mesh* mesh;
	glm::vec3 position;
	glm::vec3 velocity;
	glm::mat4 ModelMat;
	float angle;
	GLuint modelLoc;
	std::vector<GLenum> drawModeVec;
	std::vector<int> indiceCountData;
public:
	GameObject();
	~GameObject();
	std::string getName();
	void setName(std::string _name);
	void setMesh(Mesh* _mesh);
	void setPosition(float _x, float _y, float _z);
	void setVelocity(float _x, float _y, float _z);
	void UpdateDrawModes();
	void Update(float _gameTime);
	void Draw(GLuint _modelLoc);
};

