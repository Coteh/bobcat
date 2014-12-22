#pragma once
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
	void Render();

	Mesh* mesh;
	GameObject* gameObject;
	bool isEnabled;
	bool isWireFrameOn;
};

