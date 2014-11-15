#pragma once
#include "vgl.h"
struct Shader{
public:
	GLuint shaderProgram, modelLoc, cameraLoc, projectionLoc, lightingLoc;
	GLuint posAttrib, normAttrib, texAttrib, colAttrib;
};

