#include "ShaderManager.h"

ShaderManager* ShaderManager::instance;

ShaderManager::~ShaderManager(){
	shaderMap.clear();
	ShaderMap clearMap;
	clearMap.swap(shaderMap);
}

ShaderManager* ShaderManager::getInstance(){
	if (instance == nullptr){
		instance = new ShaderManager();
	}
	return instance;
}

void ShaderManager::addShader(GLuint _shader, std::string _name){
	shaderMap[_name] = _shader;
}

GLuint ShaderManager::getShader(std::string _name){
	if (shaderMap.count(_name)){ //if shader exists...
		return shaderMap[_name]; //return it
	}
	return 0; //otherwise, just return 0
}