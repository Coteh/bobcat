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
		
		bool isEnabled;
		bool isWireFrameOn;

		Material* getMaterial();
		Material* getSharedMaterial();
		void setMaterial(Material* _material);

		bool CheckShaderMatchup();
		void Render();

		__declspec(property(get = getMaterial, put = setMaterial)) Material* material;
		__declspec(property(get = getSharedMaterial)) Material* sharedMaterial;
	private:
		Material* m_material;
		Material* m_sharedMaterial;
	};

}