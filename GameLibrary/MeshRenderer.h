#pragma once
#include <glm\glm.hpp>
#include "Mesh.h"

class GameObject;

class MeshRenderer {
	friend class GameObject;
private:
	std::vector<GLenum> drawModeVec;
	std::vector<int> indiceCountData;
	void CalibrateMeshData();
public:
	MeshRenderer();
	~MeshRenderer();
	void setColor(glm::vec4 _color);
	void Render(Shader* _shader);

	Mesh* mesh;
	GameObject* gameObject;
	bool isEnabled;
	bool isWireFrameOn;

	glm::vec4 color;
};

