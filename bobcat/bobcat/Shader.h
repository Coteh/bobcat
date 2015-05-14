#pragma once
#include "External\gl_core_3_3.h"
#include <string>

namespace bobcat {

	//TO DO
	//Abstract out Shader and make derived Shader types
	//e.g. OGLShader

	struct Shader {
	public:
		GLuint shaderProgram;
		std::string name;

		GLint posAttrib, normAttrib, texAttrib, colAttrib;

		//TO DO
		//Make better constructors for Resource objects
		Shader(GLuint _shaderProgram, std::string _name);
		~Shader();

		void initAttribs();
		
		GLuint getShaderUniform(const char* _name);

		void setShaderUniformFloat(GLuint _uniformID, GLfloat _floatValue);
		void setShaderUniformFloat(const char* _name, GLfloat _floatValue);

		void enableShaderAttribs();
		void disableShaderAttribs();
	};

}