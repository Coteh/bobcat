#pragma once

#include <string>
#include <map>
#include "vgl.h"
#include "Mesh.h"

class MeshManager {
private:
	static MeshManager* instance;
	typedef std::map<const std::string, Mesh> MeshMapType;
	MeshMapType meshMap;

	//bool CheckLoaded(std::string _mesh);
	//int GetIndex(std::string _mesh);
	MeshManager();
public:
	static MeshManager* getInstance();
	~MeshManager();
	Mesh* getMesh(std::string _name);
	void addMesh(Mesh _mesh);
};

