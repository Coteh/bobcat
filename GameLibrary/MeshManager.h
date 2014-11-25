#pragma once

#include <string>
#include <map>
#include "vgl.h"
#include "Mesh.h"
#include "PLYModelReader.h"

class MeshManager {
private:
	static MeshManager* instance;
	typedef std::map<const std::string, Mesh> MeshMapType;
	MeshMapType meshMap;
	IModelReader* modelReader;

	IModelReader* determineModelReader(std::string _fileName);
	MeshManager();
public:
	static MeshManager* getInstance();
	~MeshManager();
	Mesh* getMesh(std::string _name);
	void addMesh(Mesh _mesh);
	void addMesh(std::string _fileName, std::string _meshName);
};

