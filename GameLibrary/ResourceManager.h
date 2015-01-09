#pragma once
#include <string>
#include <map>
#include "vgl.h"
#include "Mesh.h"
#include "IModelReader.h"
#include "TextureLoader.h"
#include "LogManager.h"

#define RESOUR_MODELNOTFOUND "QuestionMark"
#define RESOUR_TEXTURENOTFOUND "TextureNotFound"

namespace bobcat {

	/**
	* The Resource Manager is a singleton that facilitates the management of game resources
	* such as textures and model meshes.
	*/
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
		/**
		* Get the singleton instance.
		* @return ResourceManager singleton instance.
		*/
		static ResourceManager* getInstance();
		
		/**
		* Get a mesh of a particular name.
		* @param _name Name of the mesh to retrieve.
		* @return Mesh instance of the model/mesh with that name.
		*/
		Mesh* getMesh(std::string _name);

		/**
		* Get a texture of a particular name.
		* @param _name Name of the texture to retrieve.
		* @return Texture instance of the texture with that name.
		*/
		Texture* getTexture(std::string _name);

		/**
		* Get the GL texture ID of a texture of a particular name.
		* @param _name Name of the texture to retrieve.
		* @return GLuint id of the texture with that name.
		*/
		GLuint getTextureID(std::string _name);

		/**
		* Add a mesh.
		* @param _mesh Mesh instance to add.
		*/
		void addMesh(Mesh* _mesh);

		/**
		* Load a mesh from file, and give it a name to be associated with.
		* @param _fileName Filename of the model/mesh file to load.
		* @param _meshName Name to give to the mesh as a key. 
		*/
		void addMesh(std::string _fileName, std::string _meshName);

		/**
		* Load a texture from file, and give it a name to be associated with.
		* @param _fileName Filename of the texture image to load.
		* @param _texName Name to give to the texture as a key.
		*/
		void loadTexture(std::string _fileName, std::string _texName);

		~ResourceManager();
	};

}