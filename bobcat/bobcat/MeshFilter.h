#pragma once
#include "Component.h"
#include "Mesh.h"

namespace bobcat {

	class MeshFilter : public Component {
	private:
		Mesh* m_mesh;
	public:
		Mesh* getMesh(){
			return m_mesh;
		}
		void setMesh(Mesh* _mesh){
			m_mesh = _mesh;
		}
		__declspec(property(get = getMesh, put = setMesh)) Mesh* mesh;

		MeshFilter(){};
		~MeshFilter(){}
	};

}