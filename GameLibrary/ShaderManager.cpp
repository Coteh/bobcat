#include "ShaderManager.h"

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
	if (currShader != nullptr) disableShaderAttribs(currShader);
	Shader* shaderToUse = getShader(_name);
	glUseProgram(shaderToUse->shaderProgram);
	currShader = shaderToUse;
}

void ShaderManager::determineShaderUniforms(Shader* _shader){
	//Get model view projection matrix location
	_shader->mvpLoc = glGetUniformLocation(_shader->shaderProgram, "MVP");
	_shader->texSamplerAttrib = glGetUniformLocation(_shader->shaderProgram, "tex");
	_shader->lightingLoc = glGetUniformLocation(_shader->shaderProgram, "lightPos");
}

void ShaderManager::initShaderAttribs(Shader* _shader){
	//Grab the attribute locations from the shader
	_shader->posAttrib = glGetAttribLocation(_shader->shaderProgram, "vPosition");
	if (_shader->posAttrib < 0){
		logManager->writeLog(LogLevel::LOG_WARN, "Shader " + _shader->name + " position attribute not found!");
		logManager->printLastError();
	}
	_shader->normAttrib = glGetAttribLocation(_shader->shaderProgram, "vNormals");
	if (_shader->normAttrib < 0){
		logManager->writeLog(LogLevel::LOG_WARN, "Shader " + _shader->name + " normal attribute not found!");
		logManager->printLastError();
	}
	_shader->texAttrib = glGetAttribLocation(_shader->shaderProgram, "vTexture");
	if (_shader->texAttrib < 0){
		logManager->writeLog(LogLevel::LOG_WARN, "Shader " + _shader->name + " texture attribute not found!");
		logManager->printLastError();
	}
	_shader->colAttrib = glGetAttribLocation(_shader->shaderProgram, "vColor");
	if (_shader->colAttrib < 0){
		logManager->writeLog(LogLevel::LOG_WARN, "Shader " + _shader->name + " color attribute not found!");
		logManager->printLastError();
	}
}

void ShaderManager::disableShaderAttribs(Shader* _shader){
	glDisableVertexAttribArray(_shader->posAttrib);
	glDisableVertexAttribArray(_shader->normAttrib);
	glDisableVertexAttribArray(_shader->texAttrib);
	glDisableVertexAttribArray(_shader->colAttrib);
}

void ShaderManager::updateAttribs(std::string _shaderName, Mesh* _mesh){
	Shader* shader = getShader(_shaderName);
	
	glBindVertexArray(_mesh->getVAO());
	glBindBuffer(GL_ARRAY_BUFFER, _mesh->getVBO());

	glEnableVertexAttribArray(shader->posAttrib);
	glEnableVertexAttribArray(shader->normAttrib);
	glEnableVertexAttribArray(shader->texAttrib);
	glEnableVertexAttribArray(shader->colAttrib);

	size_t offset = 0;

	/*Specify that our coordinate data is going into attribute index 0 (vPosition), and contains
	three floats per vertex*/
	glVertexAttribPointer(shader->posAttrib, 3, GL_FLOAT,
		GL_FALSE, 11 * sizeof(GLfloat), BUFFER_OFFSET(offset));
	/*Specify that our normal data is going into attribute index 1 (vNormals), and contains
	three floats per vertex*/
	offset += (3 * sizeof(GLfloat));
	glVertexAttribPointer(shader->normAttrib, 3, GL_FLOAT,
		GL_FALSE, 11 * sizeof(GLfloat), BUFFER_OFFSET(offset));
	/*Specify that our uv data is going into attribute index 2 (vTexture), and contains
	two floats per vertex*/
	offset += (2 * sizeof(GLfloat));
	glVertexAttribPointer(shader->texAttrib, 2, GL_FLOAT,
		GL_FALSE, 11 * sizeof(GLfloat), BUFFER_OFFSET(offset));
	/*Specify that our color data is going into attribute index 3 (vColor), and contains
	three floats per vertex*/
	offset += (3 * sizeof(GLfloat));
	glVertexAttribPointer(shader->colAttrib, 3, GL_FLOAT,
		GL_FALSE, 11 * sizeof(GLfloat), BUFFER_OFFSET(offset));
}