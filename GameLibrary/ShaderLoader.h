#pragma once
// Include GLEW via vgl.h. Always include it before gl.h and glfw.h
#include "vgl.h";
// Include GLFW
#include <GLFW/glfw3.h>
// Include string
#include <string>

struct ShaderInfo {
	GLenum       type;
	const char*  filename;
	GLuint shaderID;
};

class ShaderLoader {
private:
	static const GLchar* ReadShader(const char* _fileName);
public:
	//GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	static GLuint LoadShaders(ShaderInfo* _shaders);
};

