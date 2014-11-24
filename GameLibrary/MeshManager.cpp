#include "MeshManager.h"

MeshManager* MeshManager::instance;

MeshManager::MeshManager() {
	
}

MeshManager* MeshManager::getInstance(){
	if (!instance){
		instance = new MeshManager();
	}
	return instance;
}

MeshManager::~MeshManager() {
	//Clear the map data and mesh buffers
	for (MeshMapType::iterator it = meshMap.begin(); it != meshMap.end(); ++it){
		it->second.clearBuffers();
	}
	meshMap.clear();
}

Mesh* MeshManager::getMesh(std::string _name){
	return &meshMap.find(_name)->second;
}

void MeshManager::addMesh(Mesh _mesh){
	meshMap.insert(std::make_pair(_mesh.getName(), _mesh));
}