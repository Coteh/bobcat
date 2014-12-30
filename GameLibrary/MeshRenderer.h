#pragma once
#include <glm\glm.hpp>
#include "Component.h"
#include "MeshFilter.h"
#include "Material.h"

class MeshRenderer : public Component {
public:
	MeshRenderer();
	~MeshRenderer();

	MeshFilter* meshFilter;
	Material* material;
	bool isEnabled;
	bool isWireFrameOn;

	bool CheckShaderMatchup();
	void Render();
};

