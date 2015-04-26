#pragma once
#include "Component.h"
#include "Mesh.h"

namespace bobcat {

	class MeshFilter : public Component {
	public:
		MeshFilter(){};
		virtual ~MeshFilter(){}

		Mesh* getMesh(){
			return m_mesh;
		}
		Mesh* getSharedMesh(){
			return m_sharedMesh;
		}

		void setMesh(Mesh* _mesh){
			//Delete the old mesh
			delete m_mesh;
			m_mesh = nullptr;
			//Create a copy of the mesh we're setting
			Mesh* copyMesh = Mesh::CopyMesh(*_mesh);
			//Have shared mesh point to the original mesh
			m_sharedMesh = _mesh;
			//Set the mesh to the copied mesh
			m_mesh = copyMesh;
		}

		__declspec(property(get = getMesh, put = setMesh)) Mesh* mesh;
		__declspec(property(get = getSharedMesh)) Mesh* sharedMesh;
	private:
		Mesh* m_mesh;
		Mesh* m_sharedMesh;
	};

}