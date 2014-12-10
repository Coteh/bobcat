#include "ResourceManager.h"
#include "PLYModelReader.h"
#include "PNGTextureLoader.h"
#include "TGATextureLoader.h"
#include <algorithm>
#include <iostream>
#include <sstream>

ResourceManager* ResourceManager::instance;

ResourceManager::ResourceManager() {
	logManager = LogManager::getInstance();
}

ResourceManager* ResourceManager::getInstance(){
	if (!instance){
		instance = new ResourceManager();
	}
	return instance;
}

ResourceManager::~ResourceManager() {
	//Clear the map data and mesh buffers
	for (MeshMapType::iterator it = meshMap.begin(); it != meshMap.end(); ++it){
		it->second->clearBuffers();
	}
	meshMap.clear();
	MeshMapType meshClearMap;
	meshClearMap.swap(meshMap);
	//Wipes out texture map entirely from memory
	textureMap.clear();
	TextureMapType textureClearMap;
	textureClearMap.swap(textureMap);
}

Mesh* ResourceManager::getMesh(std::string _name){
	Mesh* meshToReturn = nullptr;
	if (meshMap.count(_name)){ //find the model/mesh
		meshToReturn = meshMap.find(_name)->second; //return it if it exists
	} else if (meshMap.count(RESOUR_MODELNOTFOUND)){ //if it can't find the mesh, try to find this one...
		meshToReturn = meshMap.find(RESOUR_MODELNOTFOUND)->second; //load the "Model Not Found" mesh if it exists.
	}
	return meshToReturn;
}

Texture* ResourceManager::getTexture(std::string _name){
	if (textureMap.count(_name)){ //if texture exists...
		return textureMap[_name]; //return the texture
	} else if (textureMap.count(RESOUR_TEXTURENOTFOUND)){ //if it can't find the texture, try to find this one...
		return textureMap[RESOUR_TEXTURENOTFOUND]; //load the "Texture Not Found" texture if it exists.
	}
	return nullptr; //otherwise, just return a null pointer
}

GLuint ResourceManager::getTextureID(std::string _name){
	if (textureMap.count(_name)){ //if texture exists...
		return textureMap[_name]->texID; //return its ID
	} else if (textureMap.count(RESOUR_TEXTURENOTFOUND)){ //if it can't find the texture, try to find this one...
		return textureMap[RESOUR_TEXTURENOTFOUND]->texID; //load the "Texture Not Found" texture ID if it exists.
	}
	return -1; //otherwise, just return -1
}

IModelReader* ResourceManager::determineModelReader(std::string _fileName){
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

void ResourceManager::addMesh(Mesh* _mesh){
	meshMap.insert(std::make_pair(_mesh->getName(), _mesh));
}

void ResourceManager::addMesh(std::string _fileName, std::string _meshName){
	IModelReader* modelReader = determineModelReader(_fileName);
	if (modelReader == nullptr) return; //do not read model if model reader is null
	try{
		modelReader->readModel(_fileName);
		std::vector<GLfloat> verts = modelReader->getAllVertexData();
		std::vector<GLuint> indices = modelReader->getIndices();
		std::vector<int> indiceCountData = modelReader->getIndiceCountData();
		addMesh(new Mesh(verts, indices, _meshName, indiceCountData));
	} catch (...){
		logManager->writeLog(LogLevel::LOG_ERROR, "Could not load mesh " + _fileName);
	}
}

ITextureLoader* ResourceManager::determineTextureLoader(std::string _fileName){
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

	if (fileExtension == "png") {
		return new PNGTextureLoader();
	} else if (fileExtension == "tga"){
		return new TGATextureLoader();
	} else{ //format not supported at this time.
		return nullptr;
	}
}

void ResourceManager::loadTexture(std::string _fileName, std::string _texName){
	//Provide the file name string to the TextureLoader
	//then load the texture to the brand new texture
	Texture* brandNewTexture = new Texture();
	//Convert string to char array
	char* fileNameChars = new char[_fileName.length() + 1];
	errno_t errCode;
	errCode = strcpy_s(fileNameChars, _fileName.length() + 1, _fileName.c_str());
	//Determine TextureLoader to use
	textureLoader = determineTextureLoader(_fileName);
	if (textureLoader == nullptr) return; //do not load texture if the texture loader is null

	GLuint texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	brandNewTexture->texID = texID;

	textureLoader->LoadTextureImage(brandNewTexture, fileNameChars);

	if (brandNewTexture->imageData == nullptr){
		logManager->writeLog(LogLevel::LOG_ERROR, "Cannot load texture " + _fileName);
		logManager->printLastError();
		brandNewTexture = getTexture(RESOUR_TEXTURENOTFOUND);
		if (brandNewTexture == nullptr){ //if THAT is null as well
			return; //exit texture loading
		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, brandNewTexture->bpp, brandNewTexture->width, brandNewTexture->height, 0, brandNewTexture->type, GL_UNSIGNED_BYTE, brandNewTexture->imageData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	GLuint minFilter = GL_LINEAR_MIPMAP_LINEAR;
	// If we're using mipmaps, then we'll generate them here.
	if (minFilter == GL_LINEAR_MIPMAP_LINEAR || minFilter == GL_LINEAR_MIPMAP_NEAREST || minFilter == GL_NEAREST_MIPMAP_LINEAR || minFilter == GL_NEAREST_MIPMAP_NEAREST) {
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	//TextureLoader::LoadTGA(brandNewTexture, fileNameChars);
	//Add brand new texture to the texture map
	textureMap[_texName] = brandNewTexture;
}