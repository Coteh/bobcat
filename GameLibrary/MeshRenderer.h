#pragma once
#include <glm\glm.hpp>
#include "Mesh.h"
#include "Material.h"

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
	bool CheckShaderMatchup();
	void Render();

	Mesh* mesh;
	GameObject* gameObject;
	bool isEnabled;
	bool isWireFrameOn;

	Material* material;
};

