#include "ResourceManager.h"
#include "PLYModelReader.h"
#include "SOILTextureLoader.h"
#include "TGATextureLoader.h"
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace bobcat;

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
	for (TextureMapType::iterator it = textureMap.begin(); it != textureMap.end(); ++it){
		it->second->ClearData();
	}
	textureMap.clear();
	TextureMapType textureClearMap;
	textureClearMap.swap(textureMap);
	//Wipes out material map entirely from memory
	materialMap.clear();
	MaterialMapType materialClearMap;
	materialClearMap.swap(materialMap);
}

void ResourceManager::provideAssetPaths(std::string _modelPath, std::string _texPath) {
	//Providing model path
	modelPath = _modelPath;
	//Providing texture path
	texPath = _texPath;
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
	return nullptr; //otherwise, just return null pointer
}

GLuint ResourceManager::getTextureID(std::string _name){
	if (textureMap.count(_name)){ //if texture exists...
		return textureMap[_name]->texID; //return its ID
	} else if (textureMap.count(RESOUR_TEXTURENOTFOUND)){ //if it can't find the texture, try to find this one...
		return textureMap[RESOUR_TEXTURENOTFOUND]->texID; //load the "Texture Not Found" texture ID if it exists.
	}
	return -1; //otherwise, just return -1
}

Material* ResourceManager::getMaterial(std::string _name){
	if (materialMap.count(_name)){ //if material exists...
		return materialMap[_name]; //return the material
	}
	return nullptr; //otherwise, just return null pointer
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
		modelReader->readModel(modelPath + _fileName);
		std::vector<GLfloat> verts = modelReader->getAllVertexData();
		std::vector<GLuint> indices = modelReader->getIndices();
		std::vector<int> indiceCountData = modelReader->getIndiceCountData();
		addMesh(new Mesh(verts, indices, _meshName, indiceCountData));
	} catch (...){
		logManager->log(LogLevel::LOG_ERROR, "Could not load mesh " + _fileName);
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

	if (fileExtension == "png" || fileExtension == "jpg") {
		return new SOILTextureLoader();
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
	//Determine TextureLoader to use
	textureLoader = determineTextureLoader(_fileName);
	if (textureLoader == nullptr) return; //do not load texture if the texture loader is null

	//Generate texture ID
	GLuint texID;
	glGenTextures(1, &texID);
	//Bind texture ID
	glBindTexture(GL_TEXTURE_2D, texID);
	//Assign the newly created texture ID to the new Texture instance we just made
	brandNewTexture->texID = texID;
	//Assign name to texture
	brandNewTexture->name = _texName.c_str();

	//Convert path + filename to char array
	std::string concatStr = texPath + _fileName;
	size_t memSize = concatStr.length() + 1;
	char* fileNameChars = new char[memSize];
	errno_t errCode;
	errCode = strcpy_s(fileNameChars, memSize, concatStr.c_str());
	//Load texture using that concatenated filepath
	textureLoader->LoadTextureImage(brandNewTexture, fileNameChars);

	if (brandNewTexture->imageData == nullptr){
		logManager->log(LogLevel::LOG_ERROR, "Cannot load texture " + _fileName);
		brandNewTexture = getTexture(RESOUR_TEXTURENOTFOUND);
		if (brandNewTexture == nullptr){ //if THAT is null as well
			return; //exit texture loading
		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, brandNewTexture->bpp, brandNewTexture->width, brandNewTexture->height, 0, brandNewTexture->type, GL_UNSIGNED_BYTE, brandNewTexture->imageData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	GLuint minFilter = GL_LINEAR_MIPMAP_LINEAR;
	// If we're using mipmaps, then we'll generate them here.
	if (minFilter == GL_LINEAR_MIPMAP_LINEAR || minFilter == GL_LINEAR_MIPMAP_NEAREST || minFilter == GL_NEAREST_MIPMAP_LINEAR || minFilter == GL_NEAREST_MIPMAP_NEAREST) {
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	//Add brand new texture to the texture map
	textureMap[_texName] = brandNewTexture;
}

void ResourceManager::addMaterial(Material* _material, std::string _materialName){
	//Add brand new material to the material map
	materialMap[_materialName] = _material;
}

void ResourceManager::addTexture(Texture* _texture, std::string _textureName){
	//Add new texture to the texture map
	textureMap[_textureName] = _texture;
}