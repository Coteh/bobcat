#include "ShaderLoader.h"
#include "LogManager.h"
#include <iostream>

using namespace bobcat;

std::string ShaderLoader::shadersLoadPath;

const GLchar* ShaderLoader::ReadShader(const char* _fileName){
	FILE* inFile;
	fopen_s(&inFile, _fileName, "rb");
	if (!inFile) {
#ifdef _DEBUG
		LogManager* logManager = LogManager::getInstance();
		logManager->log(LogLevel::LOG_ERROR, "Unable to open file \"" + std::string(_fileName) + "\"");
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

GLuint ShaderLoader::LoadShaders(ShaderLoadInfo* _shaders){
	//Check if the shader isn't null before continuing
	if (_shaders == NULL) return 0;

	//Create the shader program that will be filled with shaders and then returned
	GLuint program = glCreateProgram();

	//Get the Log Manager singleton
	LogManager* logManager = LogManager::getInstance();

	ShaderLoadInfo* entry = _shaders;
	while (entry->type != GL_NONE){
		//Create shader of specified type
		GLuint shader = glCreateShader(entry->type);
		//Save the shader ID to the ShaderLoadInfo's shaderID property
		entry->shaderID = shader;
		//Concatenate shader path with filename
		std::string concatStr = std::string(shadersLoadPath) + entry->filename;
		//Read specified filename of the shader type
		const GLchar* source = ReadShader(concatStr.c_str());
		//Check if shader file was loaded
		if (source == NULL) {
			//If shader file wasn't loaded, delete all shaders
			for (entry = _shaders; entry->type != GL_NONE; ++entry) {
				glDeleteShader(entry->shaderID);
				entry->shaderID = 0;
			}

			return 0;
		}

		//Feed the shader code contents into OpenGL
		glShaderSource(shader, 1, &source, NULL);
		//Delete the source text once we're done with feeding it in
		delete[] source;

		//Compile the shader!
		glCompileShader(shader);
		//Create an int for compiled status and then get the shader compilation status parameter from shader
		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		//Is the shader compiled
		if (!compiled) {
#ifdef _DEBUG
			//In Debug Mode, create a shader compilation failed error message
			GLsizei len;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

			GLchar* glslLogStr = new GLchar[len + 1];
			glGetShaderInfoLog(shader, len, &len, glslLogStr);
			logManager->log(LogLevel::LOG_ERROR, "Shader file " + std::string(entry->filename) + " compilation failed: \n" + std::string(glslLogStr));
			delete[] glslLogStr;
#endif /* DEBUG */
			//Exit the method, returning a 0 which will signify an error with loading shader
			return 0;
		}

		//Attach the shader to the program
		glAttachShader(program, shader);

		++entry; //move the pointer up so it can point to the next shader
	}

	//Link the shaders to the program
	glLinkProgram(program);

	//Create an int for linked status, then get the link status parameter from the program
	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	//Check if the program actually linked
	if (!linked) {
#ifdef _DEBUG
		//In debug mode, display the shader linking failed error message
		GLsizei len;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

		GLchar* glslLogStr = new GLchar[len + 1];
		glGetProgramInfoLog(program, len, &len, glslLogStr);
		logManager->log(LogLevel::LOG_ERROR, "Shader file " + std::string(entry->filename) + " linking failed: \n" + std::string(glslLogStr));
		delete[] glslLogStr;
#endif /* DEBUG */
		//Delete all the shaders
		for (entry = _shaders; entry->type != GL_NONE; ++entry) {
			glDeleteShader(entry->shaderID);
			entry->shaderID = 0;
		}
		//Exit the method, returning a 0 which will signify an error with loading shader
		return 0;
	}
	//Return the loaded program ID
	return program;
}

void ShaderLoader::ProvideShaderLoadPath(std::string _shadersLoadPath) {
	//Set the path
	shadersLoadPath = _shadersLoadPath;
}