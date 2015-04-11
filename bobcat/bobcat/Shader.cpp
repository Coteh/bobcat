#include "Shader.h"

using namespace bobcat;

Shader::Shader(){

}

Shader::~Shader(){
	
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