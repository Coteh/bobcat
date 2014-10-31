#include "ShaderManager.h"
#include <iostream>

const GLchar* ShaderManager::ReadShader(const char* _fileName){
	FILE* inFile;
	fopen_s(&inFile, _fileName, "rb");
	if (!inFile) {
#ifdef _DEBUG
		std::cerr << "Unable to open file '" << _fileName << "'" << std::endl;
#endif /* DEBUG */
		return NULL;
	}

	fseek(inFile, 0, SEEK_END);
	int len = ftell(inFile);
	fseek(inFile, 0, SEEK_SET);

	GLchar* source = new GLchar[len + 1];

	fread(source, 1, len, inFile);
	fclose(inFile);

	source[len] = 0;

	return const_cast<const GLchar*>(source);
}

GLuint ShaderManager::LoadShaders(ShaderInfo* _shaders){
	if (_shaders == NULL) return 0;

	GLuint program = glCreateProgram();

	ShaderInfo* entry = _shaders;
	while (entry->type != GL_NONE){
		GLuint shader = glCreateShader(entry->type);

		entry->shader = shader;

		const GLchar* source = ReadShader(entry->filename);
		if (source == NULL) {
			for (entry = _shaders; entry->type != GL_NONE; ++entry) {
				glDeleteShader(entry->shader);
				entry->shader = 0;
			}

			return 0;
		}

		glShaderSource(shader, 1, &source, NULL);
		delete[] source;

		glCompileShader(shader);
		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
#ifdef _DEBUG
			GLsizei len;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetShaderInfoLog(shader, len, &len, log);
			std::cerr << "Shader compilation failed: " << log << std::endl;
			delete[] log;
#endif /* DEBUG */

			return 0;
		}

		glAttachShader(program, shader);

		++entry;
	}

	glLinkProgram(program);

	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked) {
#ifdef _DEBUG
		GLsizei len;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(program, len, &len, log);
		std::cerr << "Shader linking failed: " << log << std::endl;
		delete[] log;
#endif /* DEBUG */

		for (entry = _shaders; entry->type != GL_NONE; ++entry) {
			glDeleteShader(entry->shader);
			entry->shader = 0;
		}

		return 0;
	}

	return program;
}