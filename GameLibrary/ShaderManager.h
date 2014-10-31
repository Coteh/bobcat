// Include GLEW via vgl.h. Always include it before gl.h and glfw.h
#include "vgl.h";
// Include GLFW
#include <GLFW/glfw3.h>

typedef struct {
	GLenum       type;
	const char*  filename;
	GLuint       shader;
} ShaderInfo;

class ShaderManager{
private:
	static const GLchar* ReadShader(const char* _fileName);
public:
	ShaderManager(){}
	//GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	static GLuint LoadShaders(ShaderInfo* _shaders);
};