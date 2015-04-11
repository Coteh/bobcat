#pragma once
#include "vgl.h"
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
	};

}