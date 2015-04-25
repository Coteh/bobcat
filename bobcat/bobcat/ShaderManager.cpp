#include "ShaderManager.h"

using namespace bobcat;

ShaderManager* ShaderManager::instance;

ShaderManager::ShaderManager(){
	logManager = LogManager::getInstance();
}

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
	shad->name = _name;
	shaderMap[_name] = shad;
	initShaderAttribs(shad);
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

bool ShaderManager::compareCurrentShader(Shader* _shader){
	return (currShader != nullptr && currShader->shaderProgram == _shader->shaderProgram);
}

void ShaderManager::useShader(Shader* _shader){
	if (currShader != nullptr) disableShaderAttribs(currShader);
	glUseProgram(_shader->shaderProgram);
	currShader = _shader;
}

void ShaderManager::useShader(std::string _name){
	Shader* shaderToUse = getShader(_name);
	useShader(shaderToUse);
}

void ShaderManager::initShaderAttribs(Shader* _shader){
	//Grab the attribute locations from the shader
	_shader->posAttrib = glGetAttribLocation(_shader->shaderProgram, "vPosition");
	if (_shader->posAttrib < 0){
		logManager->log(LogLevel::LOG_WARN, "Shader " + _shader->name + " position attribute not found!");
	}
	_shader->normAttrib = glGetAttribLocation(_shader->shaderProgram, "vNormals");
	if (_shader->normAttrib < 0){
		logManager->log(LogLevel::LOG_WARN, "Shader " + _shader->name + " normal attribute not found!");
	}
	_shader->texAttrib = glGetAttribLocation(_shader->shaderProgram, "vTexture");
	if (_shader->texAttrib < 0){
		logManager->log(LogLevel::LOG_WARN, "Shader " + _shader->name + " texture attribute not found!");
	}
	_shader->colAttrib = glGetAttribLocation(_shader->shaderProgram, "vColor");
	if (_shader->colAttrib < 0){
		logManager->log(LogLevel::LOG_WARN, "Shader " + _shader->name + " color attribute not found!");
	}
}

void ShaderManager::disableShaderAttribs(Shader* _shader){
	glDisableVertexAttribArray(_shader->posAttrib);
	glDisableVertexAttribArray(_shader->normAttrib);
	glDisableVertexAttribArray(_shader->texAttrib);
	glDisableVertexAttribArray(_shader->colAttrib);
}

void ShaderManager::updateAttribs(Shader* _shader, Mesh* _mesh){
	glBindVertexArray(_mesh->getVAO());
	glBindBuffer(GL_ARRAY_BUFFER, _mesh->getVBO());

	GLuint numParts = 11;
	size_t offset = 0;

	/*Specify that our coordinate data is going into attribute index 0 (vPosition), and contains
	three floats per vertex*/
	glVertexAttribPointer(_shader->posAttrib, 3, GL_FLOAT,
		GL_FALSE, numParts * sizeof(GLfloat), BUFFER_OFFSET(offset));
	/*Specify that our normal data is going into attribute index 1 (vNormals), and contains
	three floats per vertex*/
	offset += (3 * sizeof(GLfloat));
	glVertexAttribPointer(_shader->normAttrib, 3, GL_FLOAT,
		GL_FALSE, numParts * sizeof(GLfloat), BUFFER_OFFSET(offset));
	/*Specify that our uv data is going into attribute index 2 (vTexture), and contains
	two floats per vertex*/
	offset += (3 * sizeof(GLfloat));
	glVertexAttribPointer(_shader->texAttrib, 2, GL_FLOAT,
		GL_FALSE, numParts * sizeof(GLfloat), BUFFER_OFFSET(offset));
	/*Specify that our color data is going into attribute index 3 (vColor), and contains
	three floats per vertex*/
	offset += (2 * sizeof(GLfloat));
	glVertexAttribPointer(_shader->colAttrib, 3, GL_FLOAT,
		GL_FALSE, numParts * sizeof(GLfloat), BUFFER_OFFSET(offset));

	glEnableVertexAttribArray(_shader->posAttrib);
	glEnableVertexAttribArray(_shader->normAttrib);
	glEnableVertexAttribArray(_shader->texAttrib);
	glEnableVertexAttribArray(_shader->colAttrib);
}

void ShaderManager::updateAttribs(std::string _shaderName, Mesh* _mesh){
	Shader* shader = getShader(_shaderName);
	updateAttribs(shader, _mesh);
}