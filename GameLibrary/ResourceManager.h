#pragma once
#include <string>
#include <map>
#include "vgl.h"
#include "Mesh.h"
#include "IModelReader.h"
#include "TextureLoader.h"
#include "LogManager.h"

class ResourceManager {
private:
	static ResourceManager* instance;

	typedef std::map<const std::string, Mesh*> MeshMapType;
	typedef std::map<const std::string, Texture*> TextureMapType;

	MeshMapType meshMap;
	TextureMapType textureMap;

	IModelReader* modelReader;
	ITextureLoader* textureLoader;

	LogManager* logManager;

	IModelReader* determineModelReader(std::string _fileName);
	ITextureLoader* determineTextureLoader(std::string _fileName);

	ResourceManager();
public:
	static ResourceManager* getInstance();
	~ResourceManager();

	Mesh* getMesh(std::string _name);
	Texture* getTexture(std::string _name);
	GLuint getTextureID(std::string _name);

	void addMesh(Mesh* _mesh);
	void addMesh(std::string _fileName, std::string _meshName);

	void loadTexture(std::string _fileName, std::string _texName);
};

