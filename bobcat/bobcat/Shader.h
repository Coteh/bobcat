#pragma once
#include "External\gl_core_3_3.h"
#include <string>

namespace bobcat {

	struct Shader {
	public:
		GLuint shaderProgram;
		std::string name;

		GLint posAttrib, normAttrib, texAttrib, colAttrib;

		Shader();
		~Shader();
		
		GLuint getShaderUniform(const char* _name);

		void setShaderUniformFloat(GLuint _uniformID, GLfloat _floatValue);
		void setShaderUniformFloat(const char* _name, GLfloat _floatValue);
	};

}