#pragma once
#include "vgl.h"
struct Shader{
public:
	GLuint shaderProgram, mvpLoc, lightingLoc;
	GLint posAttrib, normAttrib, texAttrib, colAttrib;
	std::string name;
};

