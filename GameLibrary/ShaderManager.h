#pragma once

// Include map
#include <map>
// Include Shader
#include "Shader.h"
// Include Shader Loader
#include "ShaderLoader.h"
// Include Mesh
#include "Mesh.h"

class ShaderManager{
private:
	static ShaderManager* instance;
	typedef std::map<const std::string, Shader*> ShaderMap;
	ShaderMap shaderMap;
	Shader* currShader;
	ShaderManager(){}
	void determineShaderUniforms(Shader* _shader);
	void initShaderAttribs(Shader* _shader);
public:
	~ShaderManager();
	static ShaderManager* getInstance();
	void addShader(GLuint _shaderProgram, std::string _name);
	Shader* getShader(std::string _name);
	Shader* getCurrShader();
	void useShader(std::string _name);
};