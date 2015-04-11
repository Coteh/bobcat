#include "Shader.h"

using namespace bobcat;

Shader::Shader(){

}

Shader::~Shader(){
	
}

GLuint Shader::getShaderUniform(const char* _name){
	return glGetUniformLocation(shaderProgram, _name);
}