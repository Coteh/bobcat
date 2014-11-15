#include "ShaderManager.h"

ShaderManager* ShaderManager::instance;

ShaderManager::~ShaderManager(){
	//Wipes out shader map entirely from memory
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

void ShaderManager::addShader(GLuint _shaderProgram, std::string _name){
	Shader* shad = new Shader();
	shad->shaderProgram = _shaderProgram;
	shaderMap[_name] = shad;
	initShaderAttribs(shad);
	determineShaderUniforms(shad);
}

Shader* ShaderManager::getShader(std::string _name){
	if (shaderMap.count(_name)){ //if shader exists...
		return shaderMap[_name]; //return it
	}
	return nullptr; //otherwise, just return null pointer
}

Shader* ShaderManager::getCurrShader(){
	return currShader;
}

void ShaderManager::useShader(std::string _name){
	Shader* shaderToUse = getShader(_name);
	glUseProgram(shaderToUse->shaderProgram);
	currShader = shaderToUse;
}

void ShaderManager::determineShaderUniforms(Shader* _shader){
	//Get model, camera, and projection locations
	_shader->modelLoc = glGetUniformLocation(_shader->shaderProgram, "Model");
	_shader->cameraLoc = glGetUniformLocation(_shader->shaderProgram, "Camera");
	_shader->projectionLoc = glGetUniformLocation(_shader->shaderProgram, "Perspective_Projection");
}

void ShaderManager::initShaderAttribs(Shader* _shader){
	//Grab the attribute locations from the shader
	_shader->posAttrib = glGetAttribLocation(_shader->shaderProgram, "vPosition");
	_shader->normAttrib = glGetAttribLocation(_shader->shaderProgram, "vNormals");
	_shader->texAttrib = glGetAttribLocation(_shader->shaderProgram, "vTexture");
	_shader->colAttrib = glGetAttribLocation(_shader->shaderProgram, "vColor");
}