#include "MeshManager.h"
#include <algorithm>
#include <iostream>
#include <sstream>

MeshManager* MeshManager::instance;

MeshManager::MeshManager() {
	logManager = LogManager::getInstance();
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
	Mesh* meshToReturn = nullptr;
	if (meshMap.count(_name)){
		meshToReturn = &meshMap.find(_name)->second;
	} else if (meshMap.count("QuestionMark")){
		meshToReturn = &meshMap.find("QuestionMark")->second;
	}
	return meshToReturn;
}

IModelReader* MeshManager::determineModelReader(std::string _fileName){
	std::istringstream iss(_fileName);
	std::vector<std::string> linesSplit;
	std::string line;
	while (std::getline(iss, line, '.')){
		linesSplit.push_back(line);
	}
	if (linesSplit.size() <= 1){ //no file extension provided. Return a nullptr.
		return nullptr;
	}
	std::string fileExtension = linesSplit[linesSplit.size() - 1];
	std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower);
	
	//if (fileExtension == "ply"){ Right now it's just PLY we're doing
	return new PLYModelReader();
	//}
}

void MeshManager::addMesh(Mesh _mesh){
	meshMap.insert(std::make_pair(_mesh.getName(), _mesh));
}

void MeshManager::addMesh(std::string _fileName, std::string _meshName){
	modelReader = determineModelReader(_fileName);
	if (modelReader == nullptr) return; //do not read model if model reader is null
	try{
		modelReader->readModel(_fileName);
		std::vector<GLfloat> verts = modelReader->getAllVertexData();
		std::vector<GLuint> indices = modelReader->getIndices();
		std::vector<int> indiceCountData = modelReader->getIndiceCountData();
		addMesh(Mesh(verts, indices, _meshName, indiceCountData));
	} catch (...){
		logManager->writeLog(LogLevel::LOG_ERROR, "Could not load mesh " + _fileName);
	}
}