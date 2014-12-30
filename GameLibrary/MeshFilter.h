#pragma once
#include "Component.h"
#include "Mesh.h"

class MeshFilter : public Component {
private:
	Mesh* mesh_;
public:
	Mesh* getMesh(){
		return mesh_;
	}
	void setMesh(Mesh* _mesh){
		mesh_ = _mesh;
	}
	__declspec(property(get = getMesh, put = setMesh)) Mesh* mesh;

	MeshFilter(){};
	~MeshFilter(){}
};