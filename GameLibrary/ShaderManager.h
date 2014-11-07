#pragma once

// Include map
#include <map>
// Include Shader Loader
#include "ShaderLoader.h"

class ShaderManager{
private:
	static ShaderManager* instance;
	typedef std::map<const std::string, GLuint> ShaderMap;
	ShaderMap shaderMap;
	ShaderManager(){}
public:
	~ShaderManager();
	static ShaderManager* getInstance();
	void addShader(GLuint _shader, std::string _name);
	GLuint getShader(std::string _name);
};