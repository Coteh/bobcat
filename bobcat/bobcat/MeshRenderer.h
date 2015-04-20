#pragma once
#include <glm\glm.hpp>
#include "Component.h"
#include "MeshFilter.h"
#include "Material.h"

namespace bobcat {

	class MeshRenderer : public Component {
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		MeshFilter* meshFilter;
		Material* material;
		bool isEnabled;
		bool isWireFrameOn;

		bool CheckShaderMatchup();
		void Render();
	};

}