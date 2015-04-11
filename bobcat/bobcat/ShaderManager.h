#pragma once

// Include map
#include <map>
// Include Shader
#include "Shader.h"
// Include Shader Loader
#include "ShaderLoader.h"
// Include Mesh
#include "Mesh.h"
// Include Log Manager
#include "LogManager.h"

namespace bobcat {

	class ShaderManager {
	private:
		static ShaderManager* instance;
		typedef std::map<const std::string, Shader*> ShaderMap;
		ShaderMap shaderMap;
		Shader* currShader;
		LogManager* logManager;
		ShaderManager();
		void initShaderAttribs(Shader* _shader);
		void disableShaderAttribs(Shader* _shader);
	public:
		~ShaderManager();
		static ShaderManager* getInstance();
		void addShader(GLuint _shaderProgram, std::string _name);
		Shader* getShader(std::string _name);
		Shader* getCurrShader();
		void useShader(std::string _name);
		void updateAttribs(std::string _shaderName, Mesh* _mesh);
	};

}