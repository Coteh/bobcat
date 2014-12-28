#pragma once
#include <glm\glm.hpp>
#include "Component.h"
#include "Mesh.h"
#include "Material.h"

class MeshRenderer : public Component {
	friend class GameObject;
private:
	std::vector<GLenum> drawModeVec;
	std::vector<int> indiceCountData;
	void CalibrateMeshData();
public:
	MeshRenderer();
	~MeshRenderer();

	Mesh* mesh;
	Material* material;
	bool isEnabled;
	bool isWireFrameOn;

	bool CheckShaderMatchup();
	void Render();
};

