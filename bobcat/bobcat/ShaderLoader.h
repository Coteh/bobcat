#pragma once
//Include glLoadGen
#include "External\gl_core_3_3.h"
//Include string
#include <string>

namespace bobcat {

	struct ShaderLoadInfo {
		GLenum       type;
		const char*  filename;
		GLuint shaderID;
	};

	class ShaderLoader {
	public:
		//GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
		static GLuint LoadShaders(ShaderLoadInfo* _shaders);
		static void ProvideShaderLoadPath(std::string _shadersLoadPath);
	private:
		static std::string shadersLoadPath;
		static const GLchar* ReadShader(const char* _fileName);
	};

}