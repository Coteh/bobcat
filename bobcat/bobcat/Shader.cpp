#include "Shader.h"
#include "LogManager.h"

using namespace bobcat;

Shader::Shader(GLuint _shaderProgram, std::string _name){
	shaderProgram = _shaderProgram;
	name = _name;
	initAttribs();
}

Shader::~Shader(){
	
}

void Shader::initAttribs(){
	LogManager* logManager = LogManager::getInstance();
	//Grab the attribute locations from the shader
	posAttrib = glGetAttribLocation(shaderProgram, "vPosition");
	if (posAttrib < 0){
		logManager->log(LogLevel::LOG_WARN, "Shader " + name + " position attribute not found!");
	}
	normAttrib = glGetAttribLocation(shaderProgram, "vNormals");
	if (normAttrib < 0){
		logManager->log(LogLevel::LOG_WARN, "Shader " + name + " normal attribute not found!");
	}
	texAttrib = glGetAttribLocation(shaderProgram, "vTexture");
	if (texAttrib < 0){
		logManager->log(LogLevel::LOG_WARN, "Shader " + name + " texture attribute not found!");
	}
	colAttrib = glGetAttribLocation(shaderProgram, "vColor");
	if (colAttrib < 0){
		logManager->log(LogLevel::LOG_WARN, "Shader " + name + " color attribute not found!");
	}
}

GLuint Shader::getShaderUniform(const char* _name){
	return glGetUniformLocation(shaderProgram, _name);
}

void Shader::setShaderUniformFloat(GLuint _uniformID, GLfloat _floatValue){
	//Right now, I call glUseProgram every time I want to update a uniform.
	//This is because update calls do not happen concurrently with draw calls, and thus,
	//it is not guaranteed that our shader is the current shader being used.
	//Hopefully I can find a better way to manage these uniforms in the future.
	glUseProgram(shaderProgram);
	glUniform1f(_uniformID, _floatValue);
}

void Shader::setShaderUniformFloat(const char* _name, GLfloat _floatValue){
	setShaderUniformFloat(getShaderUniform(_name), _floatValue);
}

void Shader::enableShaderAttribs(){
	glEnableVertexAttribArray(posAttrib);
	glEnableVertexAttribArray(normAttrib);
	glEnableVertexAttribArray(texAttrib);
	glEnableVertexAttribArray(colAttrib);
}

void Shader::disableShaderAttribs(){
	glDisableVertexAttribArray(posAttrib);
	glDisableVertexAttribArray(normAttrib);
	glDisableVertexAttribArray(texAttrib);
	glDisableVertexAttribArray(colAttrib);
}